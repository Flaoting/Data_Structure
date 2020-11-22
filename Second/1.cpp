/*1. 设元素值为整型的线性表L，分别采用顺序结构和链式结构存储，编写函数，用选择/冒泡排序算法实现线性表的表排序。*/
#include <iostream>
#include "SqeList.h"
#include "LinkList.h"
using namespace std;

void swap(int &a, int &b)
{
    int temp=a;
    a=b;
    b=temp;
}
//交换辅助程序

bool SqeBubbleSort(SqeList *L)
{
    if(L->length == 1 || L->length  == 0)return true;
    for (int i=0; i<L->length; i++)
    {
        for (int j=0; j<L->length-i-1; j++)
        {
            if (L->pData[j]>L->pData[j+1])
            {
                swap(L->pData[j],L->pData[j+1]);
            }
        }
    }
    return true;
}
//顺序结构的冒泡排序

bool SqeSelectSort(SqeList *L)
{
    if(L->length == 1 || L->length  == 0)return true;
    for (int i = 0; i < L->length - 1; i++)
    {
        int min_index=i;
        for (int j = i+1; j<L->length; j++)
        {
            if (L->pData[min_index]>L->pData[j])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        swap(L->pData[min_index],L->pData[i]);
    }
    return true;
}
//顺序结构的选择

// bool LinkSwap(LinkList &L, int dx, int dy)
// {
//     LNode *pre_x = L, *pre_y = L;
//     if (dy-dx==1)
//     {
//         LNode *m = q->next;
//         r->next = m;
//         q->next = m->next;
//         m->next = q;
//         return true;
//     }


    
//     while (dx--)
//     {
//         pre_x=pre_x->next;
//     }
    
//     while (dy--)
//     {
//         pre_y = pre_y->next;
//     }

//     LNode *px = pre_x->next, *py = pre_y->next;
//     LNode *nxt_x = px->next, *nxt_y = py->next;
//     pre_x->next = py;
//     py->next = nxt_x;
//     pre_y->next = px;
//     px->next = nxt_y;
// }
//交换第x,和第y个位置的元素

bool LinkBubbbleSort(LinkList &L)
{
    LNode *p = L->next,*q=p,*r=p;
    int length=0;
    while(p != NULL) 
    {
        p=p->next;
        length++;
    }
    cout << "length = "<<length<<endl;
    p = L->next;
    cout << "p->data = "<<p->data<<endl;
    for (int i=0; i<length; i++)
    {
        q = L->next;
        r = L;
        register int cnt = length - i - 1;
        cout << "cnt="<<cnt<<endl;
        cout << "q->data = "<<q->data<<endl;
        while (q->next != NULL)
        {
            // cout << "A : q->data "<< q->data <<endl;
            // cout << "B : q->next->data "<< q->next->data <<endl;
            if (q->data > q->next->data)
            {
                LNode *m = q->next;
                r->next = m;
                q->next = m->next;
                m->next = q;
                r = r->next;
                continue;
            }
            r = q;
            q = q->next;
            cout << "NO"<<endl;
        }
        cout << "YES"<<endl;
    }
    return true;
}

// bool LinkSelectSort(LinkList &L)
// {
//     LNode *p = L->next,*q=p,*r=p;
//     int length=0;
//     while(p != NULL) 
//     {
//         p=p->next;
//         length++;
//     }
//     int min_index=0;
//     for (int i=0; i<length; i++)
//     {
//         cout << "i = "<<i<<endl;
//         min_index = i;
//         p = L->next;
//         for (int k = 0; k < i; k++) 
//         {
//             p = p->next;
//         }
//         //p is point to the ist node
//         q = p->next;
//         int j = i + 1; 
//         cout << "p->data = " <<p->data<<endl;
//         cout << "q->data = " <<q->data<<endl;
//         while (q != NULL)
//         {
//             cout << "YES"<<endl;
//             if (p->data > q->data)
//             {
//                 min_index = j;
//             }
//             j ++;
//             q=q->next;
//         }
//         if (min_index != i)
//         cout << "i = " << i<<" min_index = "<<min_index<<endl;
//         cin>>i;
//         LinkSwap(L,i,min_index);
//     }
// }


// bool LinkSelectSort(LinkList &L)
// {
//     LNode *p = L->next, //当前应放入的位置
//         *k = p,         //k记录要交换的结点
//         *pre_p = L,
//         *pre_k = p,
//         *nxt_k = p,
//         *pMax;          //记录最大的数据的指针
//     while(p->next!=NULL)
//     {
//         pre_k = p;
//         k = p->next;
//         pMin = p->next;
//         while(k->next != NULL)
//         {
//             if(k->data > pMax->data)
//             {
                
//             }
//         }
//     }
// }
int main()
{
        SqeList L;
        InitList(&L);
        CreateList(&L);
        ListTraverse(L);
    //    SqeSelectSort(&L);
        SqeBubbleSort(&L);
        ListTraverse(L);
    // LinkList L; 
    // InitList(L);
    // CreateList (L,8);
    // ListTraverse (L);
    // LinkSwap(L,1,2);
    // ListTraverse(L);
    return 0;
}