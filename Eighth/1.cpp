#include <iostream>
#include <cstdlib>
#include <malloc.h>
using namespace std;
#define ElemType int
typedef struct node
{
    ElemType data;
    struct node *lchild;
    struct node *rchild;
}*BinarySortTree, BSNode;

BinarySortTree FindMin(BinarySortTree &BST)
{
    if(BST == NULL)
    {
        return NULL;
    }
    BinarySortTree cur = BST;
    while(cur != NULL)
    {
        if(cur->lchild ==NULL)
        {
            return cur;
        }
        else 
        {
            cur = cur->lchild;
        }
    }
}
//寻找最小值，返回指针

BinarySortTree InsertBSTree(BinarySortTree &BST, ElemType data)
{
    if(BST == NULL)
    {
        BST = new BSNode;
        BST->data = data;
        BST->lchild = NULL;
        BST->rchild = NULL;
        cout << BST->data<<endl;
    }
    else 
    {
        if(data < BST->data)
        {
            BST->lchild = InsertBSTree(BST->lchild,data);
        }
        else if(data > BST->data)
        {
            BST->rchild = InsertBSTree(BST->rchild,data);
        }
    }
    return BST;
}
//插入一个新的，值为data的结点

BinarySortTree DeleteNode(BinarySortTree &BST, ElemType data)
{
    if(BST == NULL)
    {
        return BST;
    }
    else if(data < BST->data)
    {
        BST->lchild = DeleteNode(BST->lchild,data);
    }
    else if(data > BST->data)
    {
        BST->rchild = DeleteNode(BST->rchild,data);
    }
    else 
    {
        if(BST->lchild != NULL && BST->rchild != NULL)
        {
            BinarySortTree tmp = FindMin(BST->rchild); //找到右子树的最小值，用来代替根节点
            BST->data = tmp->data;
            BST->rchild = DeleteNode(BST->rchild,tmp->data);
        }
        else 
        {
            BinarySortTree tmp = BST;
            if(tmp->rchild == NULL)
            {
                BST = BST->lchild;
            }
            else if(tmp->rchild == NULL)
            {
                BST = BST->rchild;
            }
            delete tmp;
        }
    }
    return BST;
}

void InOrderTraverse(BinarySortTree &BST)
{
    if(BST == NULL)
    {
        return ;
    }
    InOrderTraverse(BST->lchild);
    cout << BST->data<<" ";
    InOrderTraverse(BST->rchild);
    return;
}

int main()
{
    BinarySortTree BST = NULL,temp = NULL;
    int a[30] = {-1,7,6,9,8,10,5,2,0,10,11};
    for(int i = 1; i <= 5; i++)
    {
        InsertBSTree(BST,a[i]);
    }
    InOrderTraverse(BST);
    int t = 6;
    temp=FindMin(BST);
    DeleteNode(BST,t);
    cout << endl;
    //cout << temp->data<<endl;
    
    InOrderTraverse(BST);
    return 0;
}