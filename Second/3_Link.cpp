/*输入正整数n、m（m<n），设有n个人坐成一圈，从第1个人开始循环报数，报到m的人出列，
然后再从下一个人开始报数，报到m的人又出列，如此重复，直到所有的人都出列为止。
要求用链式结构和顺序结构实现，按出列的先后顺序输出每个人的信息。*/
#include <iostream>
#include "LinkList.h"
using namespace std;
void print(LinkList L)
{
    LNode *p = L->next,*q = p;
    do
    {
        cout << p->data << " ";
        p = p->next;
    }while (p != q);

}
void work(LinkList &L, int n, int m)
{
    LNode *p=L->next, *q = p;
    while (p->next != NULL)
    {
        p = p->next;
    } 
    
    p->next = L->next;//制作循环链表
    p = L->next; //p指向头结点的下一个
    int num=n;
    while (num > 1)
    {
        register int cnt= m-2;
        while (cnt--)
        {
            p = p->next;
        }
        q = p->next;
        num--;
        cout << "The "<<n-num<<" people is "<<q->data<<endl;
        p->next = q->next;
        free(q);
        p = p->next;
    }
    cout << "The "<<n<<" people is "<<p->data<<endl;
    return;

}
int main()
{
    int n=0, m=0;
    cin>>n>>m;
    LinkList L;
    InitList(L);
    CreateNaturalList(L,n);
    work(L,n,m);
    return 0;
}