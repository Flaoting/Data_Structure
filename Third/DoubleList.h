//双向链表的数据结构

#define ElemType int
#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct LNode
{
    LNode *prior,*next;
    ElemType data;
}LNode,*LinkList;

void CreateList(LinkList &L)
{
    int a[100] = {-1111,1345,35546,435,67,890,87,536,235323,5643,21346,23464,134564,46421323,111};
    int N = 10;
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    L->data = 0;
    LNode *p = NULL, *q=L;
    for (int i = 1; i <= N; i++)
    {
        p = (LNode*)malloc(sizeof(LNode));
        p->data = a[i];
        p->next = NULL;
        q->next = p;
        p->prior = q;
        q = p;
    }
    q->next = L->next;
    L->next->prior = q;
    return;
}
void print(LinkList &L)
{
    if(L == NULL ) 
    {
        return;
    }
    LNode *p = L->next;
    while(p != NULL )
    {
        cout << p->data<< " ";
        p = p->next;
        if(p == L->next)
        {
            break;
        }
    }
    cout << endl;
    return;
}

void ListReverse(LinkList &L)
{
    LNode *p = L->next, *q = L->next;
    do
    {
        p = p->next;
        p->prior = q;
        q = p;
        //cout << p->data<<endl;
    }while(p!=L->next);
    
    //cout << p->data <<"  "<< q->data<<endl;
    
    return ;

}

void RevPrint(LinkList &L)
{
     if(L == NULL ) 
    {
        return;
    }
    LNode *p = L->next;

    while(p != NULL )
    {
        cout << p->data<< " ";
        p = p->prior;
        if(p == L->next)
        {
            break;
        }
    }
    cout << endl;
    return;
}

