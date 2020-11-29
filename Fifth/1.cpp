#define TElemtype char
#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
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


void Pruning(BiTree T, TElemtype x,BiTree oldTree)
{
    if (T == NULL)
    {
        return;
    }
    if (T->data == x)
    {

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
int main()
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
    ShowBiTree(BT);
    cout << endl;
    LevelOrderTraverse(BT);
    cout << endl;
    PreOrderTraverse(BT);
    cout << endl;
    PostOrderTraverse(BT);
    cout << endl;
    /*DestroyBiTree(BT);
    LevelOrderTraverse(BT);*/
    int depth = 0;
    depth=BiTreeDepth(BT);
    cout << depth << endl;
    TElemtype e = '0';
    Root(BT, e);
    cout << e << endl;
    BiTNode* p = BT->lchild->rchild->rchild;
    Value(BT, p, e);
    cout << e << endl;
    /*Assign(BT, p, '9');
    LevelOrderTraverse(BT);
    cout << endl;
    DeleteChild(BT, p, 1);
    LevelOrderTraverse(BT);
    cout << endl;*/
   /* LeftChild(BT, p, q);
    cout << "p is " << p->data << " and it's leftChild is " << q->data << endl;*/
    
   /* BiTNode* q;
    Parent(BT, p, q);
    cout <<"p is "<< p->data<< " and it's parent is " << q->data << endl;
   
    LeftBrother(BT, p, q);
    cout << "p is " << p->data << " and it's leftBrother is " <<q->data<< endl;
    Assign(BT, BT->rchild, 'D');
    LevelOrderTraverse(BT);
    cout << endl;
    Pruning(BT,'D',BT);
    LevelOrderTraverse(BT);*/
    Pruning(BT, 'D', BT);
    LevelOrderTraverse(BT);
    cout << endl;
    cout << IsCompleteBiTree(BT) << endl;
    return 0;
}


