/*设线性表A、B，元素值为整型，且递减有序，编写函数，
实现下列功能：对采用顺序结构和链式结构2种存储结构，
要求在A的空间上构成一个新线性表C，
其元素为A和B元素的并集，且表C中的元素值递减有序（互不相同）*/
#include "SqeList.h"
#include "LinkList.h"
#include <iostream>
using namespace std;
bool SqeMerge(SqeList *A, SqeList *B)
{
    int j = 0;
    for (int i=0; i < B->length; i++)
    {
        ListTraverse(*A);
        //cout <<"A->length = "<<A->length<<endl;
        //cout << "i = "<<i<<endl;
        if (A->pData[0] < B->pData[i])
        {
            //cout << "Insert on 0"<<endl;
            InsertElem(A,1,B->pData[i]);
            continue;
        }

        for (; j < A->length; j++)
        {   
            //cout << "j = "<<j<<endl;
            if (j == A->length-1)
            {
                //cout << "YES"<<endl;
                if (A->pData[j]>B->pData[i])
                {
                    InsertElem(A,j+2,B->pData[i]);
                    break;
                }
                
            }
            if(A->pData[j]>=B->pData[i]&&A->pData[j+1]<=B->pData[i])
            {
                InsertElem(A,j+2,B->pData[i]);
                //cout << "now length is "<< A->length<<endl;
                break;
            }
        }
    }
    return true;
}

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
    q = B->next; 
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

int main()
{
    // SqeList A,B;
    // InitList(&A);
    // InitList(&B);
    // cout << "Please input A:"; 
    // CreateList(&A);
    // cout << "Please input B:";
    // CreateList(&B);
    // ListTraverse(A);
    // ListTraverse(B);
    // SqeMerge(&A,&B);
    // ListTraverse(A);

    LinkList A,B;
    InitList(A);
    CreateList_test2(A,8);
    ListTraverse(A);
    InitList(B);
    CreateList_test1(B,8);
    ListTraverse(B);
    LinkMerge(A,B);
    ListTraverse(A);
    return 0;
}