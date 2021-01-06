#include<cstdlib>
#include<queue>
#include <iostream>
#include <fstream>
using namespace std;

template<typename T>
struct Node
{
	int n;
	struct Node<T>** child;   //孩子的地址
	T* key;					//关键字
	bool leaf;				 //是否为叶子的标记
	Node(int t = 0) { n = t; child = nullptr; key = nullptr; leaf = true; }
	~Node() { n = 0; child = nullptr; key = nullptr; }
};

template<typename T>
class BTree
{
public:
	BTree(int m = 3)
	{
		cout << "m = " << m << endl;
		t = m; root = new Node<T>; node_num = 0;
	}
	~BTree()
	{
		PostOrder_Delete(root);
	}
	Node<T>* B_Tree_Search(const T& elem) { return search(root, elem); }  //查找元素
	void B_Tree_Insert(const T& k) { Insert(root, k); }			//插入元素k
	void B_Tree_Delete(const T& k);								//删除元素k
	void Print();												//结构化输出
	int size()const { return node_num; }                        //返回元素的个数

private:
	Node<T>* root;	//根结点
	int t;              //度数，默认是3
	int node_num;       //结点个数

	//释放整个占用的空间，给析构函数调用
	void PostOrder_Delete(Node<T>*& cur);  //后序遍历删除

	//查找部分
	Node<T>* search(Node<T>* r, const T& elem);

	//插入部分
	void B_Tree_Split_Child(Node<T>* cur, int i);
	//cur的i孩子裂变

	void Insert(Node<T>*& r, const T& k);
	//这里一点要传入指针的引用，否则会无法完成实际树的增长

	void B_Tree_Insert_NonFull(Node<T>* cur, const T& k);
	//插入非空元素

	//删除部分
	void Merge_Node(Node<T>*& cur, int i, Node<T>*& y, Node<T>*& z);
	//和并cur的第i个子结点y和第i+1个子结点z，此时y和z的key个数都是t-1

	T Search_Predecessor(Node<T>* y);
	//查找前驱

	T Search_Successor(Node<T>* z);
	//查找后继

	void Shift_To_Left_Child(Node<T>*& cur, int i, Node<T>*& y, Node<T>*& z);

	void Shift_To_Right_Child(Node<T>*& cur, int i, Node<T>*& y, Node<T>*& z);

	void B_Tree_Delete_NoNone(Node<T>* cur, const T& k);
	//删除内部结点cur的k

};

template<typename T>
Node<T>* BTree<T>::search(Node<T>* cur, const T& k) {
	int i = 0;
	while (i<cur->n && k>cur->key[i])
	{
		++i;
	}
	if (i < cur->n && k == cur->key[i]) {   //找到了，返回地址
		return cur;
	}
	else if (cur->leaf) {					//未找到，返回空
		return nullptr;
	}
	else
	{
		return search(cur->child[i], k);   //尾递归的向下查找
	}
}

template<typename T>
void BTree<T>::B_Tree_Split_Child(Node<T>* cur, int i) {
	//i是数组的下标
	Node<T>* y = cur->child[i];
	Node<T>* L, * R;   //L R是新裂变的两个片段
	L = new Node<T>;
	R = new Node<T>;
	L->n = R->n = t - 1;
	L->key = new T[t - 1];
	R->key = new T[t - 1];
	L->leaf = R->leaf = cur->child[i]->leaf;  //别忘了更改孩子的属性
	//复制键值
	for (int j = 0; j <= t - 2; j++)
	{
		L->key[j] = y->key[j];
		R->key[j] = y->key[j + t];
	}
	if (!y->leaf)
	{
		L->child = new Node<T> * [t];
		R->child = new Node<T> * [t];
		for (int j = 0; j < t; ++j)
		{
			L->child[j] = y->child[j];
			R->child[j] = y->child[j + t];
		}
	}

	//处理cur
	cur->key = (T*)realloc(cur->key, (cur->n + 1) * sizeof(T));

	cur->child = (Node<T>**)realloc(cur->child, (cur->n + 2) * sizeof(Node<T>*));

	for (int j = cur->n - 1; j >= i; j--)
	{
		//键值后移一位
		cur->key[j + 1] = cur->key[j];
	}

	cur->key[i] = y->key[t - 1];

	for (int j = cur->n; j >= i + 1; j--)
	{
		cur->child[j + 1] = cur->child[j];
	}

	cur->child[i] = L;
	cur->child[i + 1] = R;
	cur->n++;

	//销毁原来的空间

	delete[] y->child;
	delete[] y->key;
	delete y;
}

template<typename T>
void BTree<T>::Insert(Node<T>*& r, const T& k)
{
	if (B_Tree_Search(k))		//相同关键字不能插入
	{
		return;
	}
	else if (r != nullptr && r->n == 2*t - 1)
	{
		Node<T>* s = new Node<T>;
		s->leaf = false;
		s->child = new Node<T> * [1];
		s->child[0] = r;
		r = s;
		s->n = 0;
		B_Tree_Split_Child(s, 0);
		B_Tree_Insert_NonFull(s, k);
	}
	else
	{
		B_Tree_Insert_NonFull(r, k);
	}
	node_num++;  //结点个数增加
}

template<typename T>
void BTree<T>::B_Tree_Insert_NonFull(Node<T>* cur, const T& k)
{
	int i = cur->n - 1;
	if (cur->leaf)
	{  //叶子结点直接插入
		cur->key = (T*)realloc(cur->key, (cur->n + 1) * sizeof(T));
		while (i >= 0 && k < cur->key[i])
		{
			cur->key[i + 1] = cur->key[i];
			i--;
		}
		cur->key[i + 1] = k;
		cur->n++;
	}
	else
	{
		while (i >= 0 && k < cur->key[i])
		{
			i--;
		}
		i++;
		if (cur->child[i]->n == 2 * t - 1)
		{
			B_Tree_Split_Child(cur, i);
			if (k > cur->key[i])
			{
				++i;
			}
		}
		B_Tree_Insert_NonFull(cur->child[i], k);  //尾递归
	}
}

template<typename T>
void BTree<T>::Merge_Node(Node<T>*& cur, int i, Node<T>*& y, Node<T>*& z)
{
	y->key = (T*)realloc(y->key, (2 * t - 1) * sizeof(T));
	for (int j = 0; j < t - 1; ++j)
	{
		y->key[t + j] = z->key[j];
	}
	//不是叶子结点的情况下，还需要复制孩子
	if (!y->leaf)
	{
		y->child = (Node<T>**)realloc(y->child, 2 * t * sizeof(Node<T>**));
		for (int j = 0; j < t; ++j)
		{
			y->child[t + j] = z->child[j];
		}
	}
	y->key[t - 1] = cur->key[i];  //移动cur的结点补充到y
	y->n = 2 * t - 1;

	//删除cur的下移关键字
	for (int j = i; j < cur->n - 1; ++j)
	{
		cur->key[j] = cur->key[j + 1];
	}

	cur->key = (T*)realloc(cur->key, (cur->n - 1) * sizeof(T));
	//删除原来指向z的指针

	for (int j = i + 1; j <= cur->n - 1; ++j)
	{
		cur->child[j] = cur->child[j + 1];
	}
	cur->child = (Node<T>**)realloc(cur->child, (cur->n) * sizeof(Node<T>**));
	cur->child[i] = y;
	cur->n--;
	//释放掉结点z
	delete[] z->key;
	delete[] z->child;
	delete z;
	z = nullptr;
}

template<typename T>
T BTree<T>::Search_Predecessor(Node<T>* y)
{
	Node<T>* cur = y;//->child[y->n];
	while (!cur->leaf)
	{
		cur = cur->child[cur->n];
	}
	return cur->key[cur->n - 1];
}

template<typename T>
T BTree<T>::Search_Successor(Node<T>* z)
{
	Node<T>* cur = z;//->child[0];
	while (!cur->leaf)
	{
		cur = cur->child[0];
	}
	return cur->key[0];
}

template<typename T>
void BTree<T>::Shift_To_Left_Child(Node<T>*& cur, int i, Node<T>*& y, Node<T>*& z)
{
	if (y == nullptr)
	{  //防止出现空指针
		y = new Node<T>;
	}
	++y->n;
	//复制键值
	y->key = (T*)realloc(y->key, y->n * sizeof(T));
	y->key[y->n - 1] = cur->key[i];
	cur->key[i] = z->key[0];
	for (int j = 0; j < z->n - 1; j++)
	{
		z->key[j] = z->key[j + 1];
	}
	//非叶子结点的情况下复制孩子
	if (!z->leaf)
	{
		y->child = (Node<T>**)realloc(y->child, (y->n + 1) * sizeof(Node<T>*));
		y->child[y->n] = z->child[0];
		for (int j = 0; j < z->n; ++j)
		{
			z->child[j] = z->child[j + 1];
		}
		z->child = (Node<T>**)realloc(z->child, z->n * sizeof(Node<T>*));
	}
	z->n--;
	z->key = (T*)realloc(z->key, z->n * sizeof(T));
}

template<typename T>
void BTree<T>::Shift_To_Right_Child(Node<T>*& cur, int i, Node<T>*& y, Node<T>*& z) {
	if (z == nullptr)
	{
		z = new Node<T>;
	}
	z->n++;
	//复制键值
	z->key = (T*)realloc(z->key, z->n * sizeof(T));
	for (int j = z->n - 1; j > 0; --j)
	{
		z->key[j] = z->key[j - 1];
	}
	z->key[0] = cur->key[i];
	cur->key[i] = y->key[y->n - 1];
	//非叶子结点的情况下复制孩子
	if (!z->leaf)
	{
		z->child = (Node<T>**)realloc(z->child, (z->n + 1) * sizeof(Node<T>*));
		for (int j = 0; j < z->n; ++j)
		{
			z->child[j + 1] = z->child[j];
		}
		z->child[0] = y->child[y->n];
		y->child = (Node<T>**)realloc(y->child, y->n * sizeof(Node<T>*));
	}
	y->n--;
	y->key = (T*)realloc(y->key, y->n * sizeof(T));
}

template<typename T>
void BTree<T>::B_Tree_Delete_NoNone(Node<T>* cur, const T& k)
{
	//下面提到的各种情况全部参照算法导论
	if (cur->leaf)
	{   //情况1
		int i = 0;
		while (i<cur->n && k>cur->key[i])
		{
			++i;
		}
		for (int j = i + 1; j < cur->n; ++j)
		{
			cur->key[j - 1] = cur->key[j];
		}
		cur->n--;
		cur->key = (T*)realloc(cur->key, cur->n * sizeof(T));
	}

	else
	{
		int i = 0;
		while (i<cur->n && k>cur->key[i])
		{
			i++;
		}
		Node<T>* y = cur->child[i], * z = nullptr;
		if (i < cur->n)
		{
			z = cur->child[i + 1];
		}
		if (k == cur->key[i])	//情况2
		{
			if (y->n > t - 1)	//情况2a 
			{
				T k1 = Search_Predecessor(y);
				B_Tree_Delete_NoNone(y, k1);
				cur->key[i] = k1;
			}
			else if (z->n > t - 1)//情况2b 
			{
				T k1 = Search_Successor(z);
				B_Tree_Delete_NoNone(z, k1);
				cur->key[i] = k1;
			}
			else	 //情况2c
			{
				Merge_Node(cur, i, y, z);
				B_Tree_Delete_NoNone(y, k);
			}
		}
		else
		{
			//情况3
			Node<T>* p = nullptr;
			if (i > 0)
			{
				p = cur->child[i - 1];
			}
			if (y->n == t - 1)
			{
				if (i > 0 && p->n > t - 1)
				{  //情况3a
					Shift_To_Right_Child(cur, i - 1, p, y);
				}
				else if (i<cur->n && z->n>t - 1)
				{ //情况3a
					Shift_To_Left_Child(cur, i, y, z);
				}
				else if (i > 0)
				{ //情况3b
					Merge_Node(cur, i - 1, p, y);  //向左侧结点合并
					y = p;
				}
				else
				{          //情况3b
					Merge_Node(cur, i, y, z);      //向右侧合并
				}
			}
			B_Tree_Delete_NoNone(y, k);
		}
	}
}

template<typename T>
void BTree<T>::B_Tree_Delete(const T& k)
{
	Node<T>* r = root;
	if (root->n == 1 && root->child == nullptr)
	{  //删除最后一个元素
		delete[] root->key;
		delete root;
		root = nullptr;
	}

	else if (root->n == 1)
	{  //压缩根节点
		Node<T>* y = root->child[0], * z = root->child[1];
		if (y->n == z->n && y->n == t - 1)
		{
			Merge_Node(root, 0, y, z);
			root = y;
			delete[] r->child;
			delete[] r->key;
			delete r;
			B_Tree_Delete_NoNone(y, k);
		}
		else
		{
			B_Tree_Delete_NoNone(root, k);
		}
	}
	else
	{
		B_Tree_Delete_NoNone(r, k);
	}
	node_num--;  //结点个数减少一个
}

template<typename T>

void BTree<T>::Print()
{
	cout << this->node_num << "个" << endl;
	Node<T>* last = root;//last表示当前层的最右结点
	Node<T>* p = root;

	queue<Node<T>*>Q;
	if (p)
	{
		Q.push(p);
	}
	int cnt = 12;
	while (!Q.empty())
	{
		Node<T>* tmp = Q.front();
		Q.pop();

		cnt-= 3;
		for (int i = 1; i <= cnt; i++) 
		{
			cout << " ";
		}
		cout << "{";
		for (int i = 0; i < tmp->n; ++i)
		{
			cout <<tmp->key[i];
			if (i != tmp->n - 1) 
			{
				cout << " ";
			}
		}
		cout << "}";
		if (!tmp->leaf)
		{   //不是叶子结点才有孩子
			for (int i = 0; i < tmp->n + 1; ++i)
			{
				Q.push(tmp->child[i]);
			}
		}
		if (!last->leaf && tmp == last)
		{
			cout << endl;
			last = last->child[last->n];
		}

	}
	cout << endl;
}

template<typename T>
void BTree<T>::PostOrder_Delete(Node<T>*& cur)
{
	if (cur->leaf)
	{  //直接删除叶子结点
		delete[] cur->key;
		delete cur;
		cur = nullptr;
	}
	else
	{ //递归地删除每个孩子
		for (int i = 0; i < cur->n + 1; ++i)
		{
			PostOrder_Delete(cur->child[i]);
		}
		delete[] cur->key;
		delete cur;
		cur = nullptr;
	}
}
void Menu() {
	cout << "========B-Trees 的设计与实现========" << endl;
	cout << "操作说明:" << endl;
	cout << "1.建立B-Tree" << endl;
	cout << "2.遍历输出B-Tree" << endl;
	cout << "3.删除元素" << endl;
	cout << "4.插入元素" << endl;
	cout << "5.退出" << endl;
}

int main()
{
	Menu();
	BTree<int>* bt = nullptr;
	bool flag = true;
	while (flag) 
	{
		cout << "请输入操作编号:";
		int n;
		cin.clear(); cin.sync();
		cin >> n;
		switch (n) 
		{
		case 1:
			if (bt != nullptr)
			{
				cout << "树已经存在!" << endl;
				continue;
			}
			else
			{
				cout << "1.手动建立" << endl;
				cout << "2.从文件读取" << endl;
				cout << "请输入操作编号:";
				cin >> n;
				int a, b = 2;
				if (n == 1)
				{
					cout << "输入元素个数n:";
					cin >> a;
					if (b < 2)
					{
						cout << "度数太小!" << endl;
						continue;
					}
					bt = new BTree<int>(b);
					cout << "输入" << n << "个元素:" << endl;
					for (int i = 0; i < a; i++)
					{
						int c;
						cin >> c;
						bt->B_Tree_Insert(c);
					}
				}
				else 
				{
					fstream file("1.txt", ios::in);
					if (!file)
					{
						cout << "文件打开失败" << endl;
						continue;
					}
					file >> a;
					bt = new BTree<int>(b);
					for (int i = 0; i < a; i++)
					{
						int c;
						file >> c;
						bt->B_Tree_Insert(c);
					}
				}
			}
			break;
		case 2:
			if (bt == nullptr) 
			{
				cout << "当前没有建立B树!" << endl;
			}
			else if (bt->size() <= 0)
			{
				cout << "B树中无元素!" << endl;
			}
			else
			{
				bt->Print();
			}
			break;
		case 3:
			if (bt == nullptr) 
			{
				cout << "当前没有建立B树!" << endl;
			}
			else if (bt->size() <= 0) 
			{
				cout << "B树中无元素!" << endl;
			}
			else
			{
				cout << "请输入要删除的元素:";
				int k;
				cin >> k;
				bt->B_Tree_Delete(k);
			}
			break;
		case 4:
			if (bt != nullptr)
			{
				cout << "请输出插入的元素:";
				int  c;
				cin >> c;
				bt->B_Tree_Insert(c);
			}
			else {
				cout << "B树未建立！" << endl;
			}
			break;
		case 5:
			delete bt;
			bt = nullptr;
			flag = false;
			break;
		default:
			cout << "输入无效!" << endl;
			cin.clear();            //clear bad input flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  //适应gnu
			    
		}
	}
	system("pause");
	return 0;
}

