#define TElemtype char
#include <iostream>
#include <fstream>
#include <malloc.h>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;

typedef struct BiTNode
{
    TElemtype data;
    struct BiTNode* lchild, * rchild;

}BiTNode, * BiTree;

void print(TElemtype e)
{
    cout << e;
}

bool InitBitree(BiTree& T)
{
    T = NULL;
    return true;
}
//构造一颗空的二叉树，空即没有结点

void DestroyBiTree(BiTree& T)
{
    if (T == NULL)
    {
        return ;
    }
    if (T->lchild != NULL)
    {
        DestroyBiTree(T->lchild);
    }
    if (T->rchild != NULL)
    {
        DestroyBiTree(T->rchild);
    }
    free(T);
    T = NULL;
    return;
}
//销毁一颗树

BiTree CreateBiTree(BiTree T, fstream &file)
{
    if (file.eof())
    {
        return NULL;
    }

    TElemtype data;         //试验阶段数据类型为char型
    file >> data;
    if (data == '#')
    {
        return NULL;
    }
    else
    {
        T = (BiTNode *)malloc(sizeof(BiTNode));
        T->data = data;
        T->lchild = CreateBiTree(T->lchild, file);
        //cout << "LeftChild over i is " << i <<" data is "<< data <<endl;
        T->rchild = CreateBiTree(T->rchild, file);
        //cout << "RightChild over i is " << i << " data is " << data << endl;
    }
    return T;
}
//建树,利用递归的方法，先建立左子树，再建立又子树



bool BiTreeEmpty(BiTree T)
{
    if (T == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//判断树是否为空树

int BiTreeDepth(BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    if (T->lchild == NULL && T->rchild == NULL)
    {
        return 1;
    }
    return max(BiTreeDepth(T->lchild), BiTreeDepth(T->rchild))+1;
}
//返回树的深度

bool Root(BiTree T, TElemtype& e)
{
    if (T == NULL)
    {
        return false;
    }
    else
    {
        e = T->data;
        return true;
    }
}
//二叉树存在，返回二叉树跟的元素

bool Value(BiTree T, BiTNode* cur_p, TElemtype& e)
{
    if (T == NULL)
    {
        return false;
    }
    else
    {
        e = cur_p->data;
        return true;
    }
}
// 返回cur_p指向的结点的值e

void FindFather(BiTree T, BiTNode* cur_p, BiTree& parent)    //parent为指针的引用
{
    if (T == NULL)
    {
        return;
    }
    if (T->lchild == cur_p)
    {
        parent = T;
        return;
    }
    if (T->rchild == cur_p)
    {
        parent = T;
        return;
    }
    FindFather(T->lchild, cur_p, parent);
    FindFather(T->rchild, cur_p, parent);
    return;
}
//递归寻找双亲的辅助函数

bool Parent(BiTree T, BiTNode* cur_p, BiTree& parent)
{
    if (T == NULL)
    {
        parent = NULL;
        return false;
    }

    if (T == cur_p)
    {
        //当传入指针为根节点时候，他没有双亲
        parent = NULL;
        return false;
    }

    parent = NULL;

    //上边情况都不是的话，那么递归查找他的双亲

    FindFather(T, cur_p, parent);
    if (parent == NULL)
    {
        //没有找到双亲的情况
        return false;
    }
    else
    {
        return true;
    }
}
//通过引用返回双亲指针

bool LeftChild(BiTree T, BiTNode* cur_p, BiTree &leftChild)
{
    if (T == NULL)
    {
        return false;
    }

    if (cur_p->lchild != NULL)
    {
        leftChild = cur_p->lchild;
        return true;
    }
    else
    {
        leftChild = NULL;
        return false;
    }
}
//返回左儿子的指针

bool RightChild(BiTree T, BiTNode* cur_p, BiTree &rightChild)
{
    if (T == NULL)
    {
        rightChild = NULL;
        return false;
    }

    if (cur_p->rchild != NULL)
    {
        rightChild = cur_p->rchild;
        return true;
    }
    else
    {
        rightChild = NULL;
        return false;
    }
}
//返回右儿子的指针

bool LeftBrother(BiTree T, BiTNode* cur_p, BiTree& leftBrother)
{
    BiTNode *parent = NULL;
    Parent(T, cur_p, parent);
    cout << "yes" << endl;
    cout << "parent is " << parent << endl;
    if (parent == NULL)
    {
        leftBrother = NULL;
        return false;
    }

    if (parent->lchild != NULL && parent->lchild != cur_p)
    {
        leftBrother = parent->lchild;
        return  true;
    }
    else
    {
        leftBrother = NULL;
        return false;
    }
}
//返回左兄弟的指针

bool RightBrother(BiTree &T, BiTNode* cur_p, BiTree& rightBrother)
{
    BiTNode* parent = NULL;
    Parent(T, cur_p, parent);
    if (parent == NULL)
    {
        rightBrother = NULL;
        return false;
    }

    if (parent->rchild != NULL && parent->rchild != cur_p)
    {
        rightBrother = parent->rchild;
        return  true;
    }
    else
    {
        rightBrother = NULL;
        return false;
    }
}
//返回右兄弟的指针 

void visit(BiTNode* cur_p)
{
    if (cur_p == NULL)
    {
        return;
    }

    else
    {
        print(cur_p->data);
        return;
    }

}
//visit 访问结点的函数

void PreOrderTraverse(BiTree T)
{
    visit(T);
    if (T == NULL)
    {
        return;
    }
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
    return;
}
//进行先序遍历

void InOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        visit(T);
        return;
    }
    InOrderTraverse(T->lchild);
    visit(T);
    InOrderTraverse(T->rchild);
    return;
}
//中序遍历

void PostOrderTraverse(BiTree T)
{
    if (T == NULL)
    {
        visit(T);
        return;
    }
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    visit(T);
    return;
}
//实现后序遍历

void LevelOrderTraverse(BiTree T)
{
    if (T == NULL) 
    {
        cout << "At least you still have an empty set " << endl;
        return;
    }
    queue <BiTNode*> Q;
    BiTNode* p, * q;
    p = T;
    Q.push(p);
    while (!Q.empty())
    {
        q = Q.front();
        visit(q);
        Q.pop();
        if (q->lchild != NULL)
        {
            Q.push(q->lchild);
        }
        if (q->rchild != NULL) 
        {
            Q.push(q->rchild);
        }
    }
    return;
}
//实现层次遍历

bool Assign(BiTree T, BiTree& cur_p, TElemtype value)
{
    if (T == NULL)
    {
        return false;
    }
    cur_p->data = value;
    return true;
}
//将cur_p指向结点的data值赋值为value


bool InsertChild(BiTree T, BiTNode* cur_p, bool LR, BiTree c)
{
    if (T == NULL)
    {
        return false;
    }
    BiTNode* temp = NULL;
    if (!LR)
    {
        temp = cur_p->lchild;
        cur_p->lchild = c;
        c->rchild = temp;
    }
    else
    {
        temp = cur_p->rchild;
        cur_p->rchild = c;
        c->rchild = temp;
    }
    return true;
}
//插入c为p的左或者右子树，c的右子树为p原来被替换的子树

bool DeleteChild(BiTree T, BiTNode* cur_p, bool LR)
{
    if (T == NULL)
    {
        return false;
    }
    if (!LR)
    {
        DestroyBiTree(cur_p->lchild);
    }
    else
    {
        DestroyBiTree(cur_p->rchild);
    }
    return true;
}

void ShowBiTree(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    print(T->data);
    if (T->lchild != NULL || T->rchild != NULL)
    {
        cout << "( ";
        ShowBiTree(T->lchild);
        cout << ", ";
        ShowBiTree(T->rchild);
        cout << " )";
    }
    return;
}


void Pruning(BiTree& T, TElemtype x,BiTree oldTree)
{
    if (T == NULL)
    {
        return;
    }
    if (T->data == x)
    {
        if(T == oldTree)
        {
            DestroyBiTree(T);
            return;
        }
        BiTNode* parent;
        Parent(oldTree, T, parent);
        if (parent->lchild == T)
        {
            parent->lchild = NULL;
        }
        if (parent->rchild == T)
        {
            parent->rchild = NULL;
        }
        DestroyBiTree(T);
        return;
    }
    Pruning(T->lchild, x, oldTree);
    Pruning(T->rchild, x, oldTree);
    return;
}

bool IsCompleteBiTree(BiTree T)
{
    BiTNode* p = NULL;
    queue<BiTNode*> Q;
    int flag = 0;
    Q.push(T);
    while (!Q.empty()) 
    {
        p = Q.front();
        Q.pop();
        if (p->lchild == NULL && p->rchild == NULL)     //没儿子 
        {   
            flag = 1;
        }
        else if (p->lchild == NULL && p->rchild != NULL)    //只有右儿子
        {
            return false;
        }
        else if (p->lchild != NULL && p->rchild == NULL)    //只有左儿子
        {
            if (flag != 0)
            {
                return false;       //前边已经有度为1，或者叶子结点了，你却有了一个儿子
            }
            else 
            {
                flag = 1;
            }
        }
        else
        {
            if (flag > 0)
            {
                return false;   //此前已经有度不大于1的结点被访问过
            }
            Q.push(p->lchild);
            Q.push(p->rchild);
        }
    }
    return true;
}

void PreOrderTraverseWithoutRecursion(BiTree T)
{
    if (T == NULL)
    {
        return;
    }
    stack <BiTNode*> S;
    BiTNode* p, * q;
    p = T;
    S.push(p);
    while (!S.empty())
    {
        q = S.top();
        S.pop();
        visit(q);
        if (q->rchild != NULL)
        {
            S.push(q->rchild);
        }
        if (q->lchild != NULL)
        {
            S.push(q->lchild);
        }
    }
}
//非递归方法实现先序遍历

void InOrderTraverseWithoutRecursion(BiTree T) 
{
    if (T == NULL)
    {
        return;
    }
    stack <BiTNode*> S;
    BiTNode *p;
    p = T;
    while (!S.empty() || p != NULL)
    {
        while (p != NULL) 
        {
            S.push(p);
            p = p->lchild;
        }
        if (!S.empty())  //栈顶元素没有左儿子 
        {
            p = S.top();
            visit(p);
            S.pop();
            p = p->rchild;
        }
    }
    return;
}
//非递归方法实现中序遍历


void PostOrderTraverseWithoutRecursion(BiTree T) 
{
    if (T == NULL)
    {
        return;
    }
    stack <BiTNode*> S;
    BiTNode* cur = NULL, *pre = NULL;
    cur = T;
    S.push(cur);
    while (!S.empty())
    {
        cur = S.top();
        if ((cur->lchild == NULL && cur->rchild == NULL) || (pre != NULL && (pre == cur->lchild || pre == cur->rchild))) 
        {
            visit(cur);
            S.pop();
            pre = cur;
        }
        else
        {
            if (cur->rchild != NULL)
            {
                S.push(cur->rchild);
            }
            if (cur->lchild != NULL) 
            {
                S.push(cur->lchild);
            }
        }
    }
    return;
}

//非递归方法实现后序遍历


// 一个数组，数组长度不低于二叉树的高度，为了简便起见，这里假设是一百,
// 自己使用得时候可以改成动态数组(或链表)

int vec_left[100] = {0};

// 显示二叉树的函数，只要调用Display(root, 0)即可
void DisplayBinaryTree(BiTree &root, int ident)
{
    if(ident > 0)
    {
        for(int i = 0; i < ident - 1; ++i)
        {
            printf(vec_left[i] ? "|   " : "    ");
        }
        printf(vec_left[ident-1] ? "|-- " : "'-- ");
    }
    if(! root)
    {
        cout << "(null)" <<endl;
        return;
    }
 
    cout << root->data << endl;
    if(!root->lchild && !root->rchild)
    {
        return;
    }
 
    vec_left[ident] = 1;
    DisplayBinaryTree(root->rchild, ident + 1);
    vec_left[ident] = 0;
    DisplayBinaryTree(root->lchild, ident + 1);

}

int CaculateWidthOfBinaryTree(BiTree &BT)
{
    BiTNode *p = BT;
    queue <BiTNode*> Q;
    Q.push(BT);
    Q.push(NULL);
    
    int max_cnt = -1;
    int cnt = 1;
    bool flag = false;

    while(!Q.empty())
    {
        p = Q.front();
        Q.pop();
        if(p == NULL)
        {
            if(flag)
            {
                break;
            }
            max_cnt = max(max_cnt,cnt);
            cnt = 0;
            Q.push(NULL);
            flag = true;
            continue;
        }
        flag = false;
        if(p->lchild != NULL)
        {
            cnt ++;
            Q.push(p->lchild);
        }
        if(p->rchild != NULL)
        {
            cnt ++;
            Q.push(p->rchild);
        }
    }
    return max_cnt;
}

void test()
{
    fstream file("E://vscode//C++//Data_structure//Fifth//CreateBiTree.txt", ios::in);
    if (!file)
    {
        cout << "file can't be opened ！" << endl;
        exit(0);
    }
    BiTree BT;
    InitBitree(BT);
    BT = CreateBiTree(BT, file);
    //ShowBiTree(BT);
    cout << endl;
    DisplayBinaryTree(BT,0);
    //Pruning(BT,'A',BT);
    
    // LevelOrderTraverse(BT);
    Pruning(BT, 'G', BT);
    // cout << endl;
    // cout << IsCompleteBiTree(BT) << endl;
    int width = 0;
    width = CaculateWidthOfBinaryTree(BT);
    DisplayBinaryTree(BT,0);
    cout << "The width of BinaryTree is "<< width << endl;
    return ;
}


