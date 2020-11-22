/*2.37 设带头结点的双向循环链表的线性表L = (a1,a2,a3.....an),设计时间复杂度为O(n)的算法
，将其改造为L=(a1,a3...an...a4,a2)*/
#include "DoubleList.h"

void choice(LinkList &L)
{
    if (L == NULL)
    {
        return ;
    }
    LNode *p = L->next, *q = NULL, *r = L->next->prior;
    cout << r->data<<"hhhhhhh"<<endl;
    int length = 0;
    do
    {
        length ++;
        p = p->next;
    }while(p != L->next);
    //cout << "Length is "<<length<<endl;
    p = L->next;

    if (length % 2 == 1)        //当长度为奇数的时候
    {
        do
        {
            q = p->next->next;
            p->next = q;
            q->prior = p;
            p = q;
        }while(p->next != L->next);
        p = p->next;
        q = p;
        do
        {
            q = p->prior->prior;
            p->next = q;
            q->prior = p;
            p = q;
        }while(p->prior != L->next);    
    }
    else            //当长度为偶数的时候
    {
        do
        {
            q = p->next->next;
            p->next = q;
            q->prior = p;
            p = q;
            cout << "p->data  :"<<p->data<<endl;
        }while(p != L->next);
        cout << "hhh now data is "<< p->data<<endl;
        q = r;
        cout << q->data<<endl;
        do
        {
            r = q->prior->prior;
            p->next = q;
            q->prior = p;
            p = q;
            q = r;
            //cout << "p->data  :" <<p->data<<endl;
        }while(p->prior != L->next);

    }
    return;
}
//根据题目要求，进行单数双数的选择

int main()
{
    LinkList L;
    CreateList(L);
    print(L);
    choice(L);
    print(L);
    return 0;
}