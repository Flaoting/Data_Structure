#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct LNode
{
    int data;               //数据域
    struct LNode *next;     //指针域
}LNode,*LinkList;

bool InitList(LinkList &L)
{
    L = (LNode*)malloc(sizeof(LNode));   //这里申请了一个头结点,链表指针指向了头结点
    if(L == NULL) exit (0);
    L->data = 0;
    L->next=NULL;
    return true;
}

bool DestroyList (LinkList &L)
{
    LNode *p=L->next,*q=p;
    L->next=NULL;
    while (p)
    {
        p=p->next;
        free(q);
        q=p;
    }
    free (L);
    L = NULL; 
    return true;

}

//创建一个有n个元素的链式结构的线性表
bool CreateList(LinkList &L,int n)
{
    LNode *p = L;
    int a[100]={8,7,6,5,4,3,2,1,4,2,4,3,5,6,7,8,9,2,5,4};
    for (int i = 0; i < n; i ++)
    {
        p->next = (LNode *)malloc(sizeof(LNode));
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    return true;
}
bool CreateNaturalList(LinkList &L,int n)
{
    
    LNode *p = L;
    for (int i = 1; i <= n; i ++)
    {
        p->next = (LNode *)malloc(sizeof(LNode));
        p = p->next;
        p->data = i;
    }
    p->next = NULL;
    return true;
}
bool CreateListByHand(LinkList &L)
{
    int n,t=0;
    cout << "Please input the number of this series :   ";
    cin >> n;
    LNode *p = L;
    for (int i = 1; i <= n; i ++)
    {
        p->next = (LNode *)malloc(sizeof(LNode));
        p = p->next;
        cin >> t;
        p->data = t;
    }
    p->next = NULL;
    return true;
}
bool CreateList_test1(LinkList &L,int n)
{
    LNode *p = L;
    int a[100]={11445,1112,998,965,456,258,154,123,101,99,95,56,55,12,7};
    for (int i = 0; i < n; i ++)
    {
        p->next = (LNode *)malloc(sizeof(LNode));
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    return true;
}
bool CreateList_test2(LinkList &L,int n)
{
    LNode *p = L;
    int a[100]={33441,2777,1225,1023,1001,986,952,845,687,514,503,421,333,212,111,28,17,2,-22332};
    for (int i = 0; i < n; i ++)
    {
        p->next = (LNode *)malloc(sizeof(LNode));
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    return true;
}
bool CreateList_test3(LinkList &L,int n)
{
    LNode *p = L;
    int a[100]={2,17,25,36,59,98,122,158,199,202,1512,25215,54545,458481,44787454};
    for (int i = 0; i < n; i ++)
    {
        p->next = (LNode *)malloc(sizeof(LNode));
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    return true;
}
bool CreateList_test4(LinkList &L,int n)
{
    LNode *p = L;
    int a[100]={-110,-2,36,58,999,1214,2589,6545,6589,6666,8899,10216,11245,56254,5658265};
    for (int i = 0; i < n; i ++)
    {
        p->next = (LNode *)malloc(sizeof(LNode));
        p = p->next;
        p->data = a[i];
    }
    p->next = NULL;
    return true;
}
bool ListTraverse (LinkList L)
{
    if (L)
    {

        LNode *p=L->next;
        while (p)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
        return true;
    }
    else 
    {
        return false;
    }
   
}

//清空链表
bool ClearList (LinkList &L)
{
    LNode *p=L->next,*q=p;
    while (p)
    {
        p = p->next;
        free(q);
        q=p;
    }
    L->next = NULL;
    return true;
}
//judge list whether empty
bool ListEmpty (LinkList &L)
{
    if ( L->next == NULL) return true; //if list has one node is head
    else return false;
}

int ListLength(LinkList &L)
{
    if(!L) return -1;
    LNode *p = L->next;
    int cnt = 0;
    while(p)
    {
        p = p->next;
        cnt ++;
    }
    return cnt;
}

bool GetElem (LinkList &L, int pos, int &e)
{
    int length = ListLength(L);
    if (pos<1 || pos > length) return false; //如果数据位置非法，那么就返回操作失败的标志

    LNode *p = L->next;
    for (int i=1;i<pos;i++)
    {
        p = p->next;
    }

    e = p->data;
    return true;
}

int LocateElem (LinkList &L, int e)
{
    LNode *p = L->next;
    int cnt = 1;
    while (p)
    {  
        if (p->data == e) return cnt;
        p = p->next;
        cnt ++ ;
    }
    return 0;
}

bool PriorElem(LinkList &L, int cur_e, int &pre_e)
{
    LNode *p = L->next, *q = p;
    
    while (p)
    {
        if (p->data == cur_e && p != L->next)
        {
            pre_e = q->data;
            return true; 
        }
        q = p;
        p = p->next;
    }
    return false;
}

bool NextElem(LinkList &L, int cur_e, int &next_e)
{
    LNode *p = L->next;
    while(p->next)
    {
        if(p->data == cur_e)
        {
            next_e = p->next->data;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool SetElem(LinkList &L, int pos ,int &e)
{

    int length = ListLength (L);
    if (pos<1 || pos > length )
    {
        cout << "Set position is overflow !"<<endl;
        return false; //如果超出范围的话 
    }
    LNode *p = L->next;
    for (int i = 1; i < pos; i++) p = p->next;
    int temp  = p->data;
    p->data = e;
    e = temp;
    return true;
}

bool InsertElem(LinkList &L, int pos, int e)
{
    int length = ListLength (L);
    if (pos < 1 || pos > length + 1 ) //可以加在最后一个，所以长度要加一
    {
        cout << "Set position is overflow !"<<endl;
        return false; //如果超出范围的话 
    }
    LNode *p = L->next,*q =NULL;
    
    for (int i = 2; i < pos; i ++) p = p->next; //this node is at the position of pos-1
    q = (LNode *)malloc( sizeof(LNode) );
    if (pos == 1)
    {
        q->data = e;
        q->next = L->next;
        L->next = q;
    }

    else 
    {
        q->data = e;
        q->next = p->next;
        p->next = q;
    }
   
    return true;
}

bool DeleteElem(LinkList &L, int pos, int &e)
{
    int length = ListLength (L);
    if (pos < 1 || pos > length ) //可以加在最后一个，所以长度要加一
    {
        cout << "Set position is overflow !"<<endl;
        return false; //如果超出范围的话 
    }

    LNode *p = L->next,*q=p;
    for (int i = 2; i < pos; i ++) p=p->next; //找到pos前边的一个，就是位置是pos-1
    if (pos == 1)
    {
        e = L->next->data;
        q = L->next;
        L->next = L->next->next;
        free(q); 
        return true;
    }
    e = p->next->data; //e是他下一个元素的值 
    q = p->next;
    p->next = q->next;
    free(q);
    return true;

}


// bool ListReverse(LinkList &L)
// {
//     if (L == NULL) return false;
//     LNode *p=L->next;
//     LinkList RL = (LNode *)malloc(sizeof(LNode));
//     RL->next = NULL;
//     while (p != NULL)
//     {
//         L->next=p->next;
//         p->next=RL->next;
//         RL->next=p;
//         p = L->next;
//     }
//     L=RL;
//     return true;
// }