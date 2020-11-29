// 3. 设二叉树采用二叉链表存储，编写函数，对二叉树中每个元素值为x的结点，删除以它为根的子树，并释放相应空间。（习题集6.45）
#include "BiTree.h"

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
    BiTNode *p = BT->rchild->lchild;
    Assign(BT,p,'D');
    Pruning(BT,'D',BT);
    LevelOrderTraverse(BT);
    return 0;
}
