#include <iostream>
#include "LinkList.h"
using namespace std;

bool LinkMerge(LinkList &A, LinkList &B)
{
    LNode *p = A->next, *q = B->next, *L = B; //L可以看做新的表头
    LNode *r1 = p, *r2 = q;

    while(p != NULL && q != NULL && p->data < q->data)
    {
        r2 = q->next;
        q->next = A->next;
        A->next = q;
        q = r2;
        p = A->next;
    }
    p = A->next; 
    // cout <<"A : p->data = "<<p->data<<endl;
    // cout <<"B : q->data = "<<q->data<<endl;
    while (q != NULL)
    {
        r2 = q->next;
        while(p->data > q->data && p->next->data > q->data && p->next != NULL)
        {
            p = p->next;
            // cout << "After p = p->next"<<endl;
            // cout <<"p->data = "<<p->data<<endl;
            // cout <<"q->data = "<<q->data<<endl;
            if (p->next == NULL)
            {
                break;
            }
        }
        q->next = p->next;
        p->next = q;
        q = r2;
    }
    while(q != NULL &&p->next == NULL)
    {
        r2 = q->next;
        q->next = p->next;
        p->next = q;
        q = r2;
        p = p->next;
    }
    return true;
}
//两个递减序列进行合并

bool ListReverse(LinkList &L)
{
    if (L == NULL) return false;
    LNode *p=L->next;
    LinkList RL = (LNode*)malloc(sizeof(LNode));
    RL->next = NULL;
    while (p != NULL)
    {
        L->next=p->next;
        p->next=RL->next;
        RL->next=p;
        p = L->next;
    }
    L->next = RL->next;
    return true;
}
//逆序的函数
int main()
{
    LinkList A,B;
    InitList(A);
    InitList(B);

    CreateList_test3(A,8);
    CreateList_test4(B,8);

    ListTraverse(A);    
    ListTraverse(B);

    ListReverse(A);
    ListReverse(B);
    
    ListTraverse(A);    
    ListTraverse(B);

    LinkMerge(A,B);
    ListTraverse(A);
}