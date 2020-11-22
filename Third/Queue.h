#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*QueuePtr;

typedef struct Queue
{
    QueuePtr front;
    QueuePtr rear;
}Queue;

extern void print();//调用的函数要写一个元素的print函数
//打印元素的函数


bool QueueEmpty(const Queue &Q)
{
    if(Q.front == Q.rear) //空队的标准是对头和队尾的指针相同
    {
        return true;
    }
    else
    {
        return false;
    }
}
//判断队列是否为空队列，是的话返回true，否则返回false

bool InitQueue(Queue &Q)
{
    Q.front = Q.rear = (LNode*)malloc(sizeof(LNode));
    if( Q.front == NULL)
    {
        cout << "Memory is overflow "<<endl;
        exit(0);
    }
    Q.front->next = NULL;
    return true;
}
//队列的初始化

bool DestroyQueue(Queue &Q)
{
    if(Q.front == NULL && Q.rear == NULL)
    {
        return true;
    }

    QueuePtr p,q;
    p = Q.front;
    while(p != Q.rear)
    {
        q = p;
        p = p->next;
        free(q);
    }
    free(Q.rear);
    Q.front = NULL;
    Q.rear = NULL;
    return true; 
}
//销毁队列

bool ClearQueue(Queue &Q)
{
    if(QueueEmpty(Q))
    {
        cout << "This queue is empty ,no need to clear "<<endl;
        return false;
    }

    QueuePtr p,q;
    p = Q.front->next;

    while(p != Q.rear)
    {
        q = p;
        p = p->next;
        free(q);
    }  
    free(Q.rear);

    Q.rear = Q.front;
    return true;
}
//清空队列

int QueueLength(const Queue &Q)
{
    if(QueueEmpty(Q))
    {
        return 0;//空队列长度直接返回0
    }
    QueuePtr p;
    p = Q.front->next;
    int length = 0;
    while(p->next != NULL)
    {
        length++;
        p = p->next;
    }
    return length;
}
//计算队列的长度

bool GetHead(const Queue &Q, ElemType &e)
{
    if(Q.front != NULL)
    {
        return false;
    }
    e = Q.front->next->data;
    return true;
}
//取出队头元素

bool QueueTraverse(const Queue &Q)
{
    if (QueueEmpty(Q))
    {
        cout << "Queue is empty ,so you can't traverse"<<endl;
        return false;
    }

    QueuePtr p = Q.front->next;
    
    while(p != NULL)
    {
        print(p->data);
        cout << " ";
        p = p->next;
    }
    cout << endl;
}
//遍历队列中的元素

bool EnQueue(Queue &Q, ElemType e)
{
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(s == NULL)
    {
        cout << "Memory is overflow "<<endl;
        exit (0);
    }
    s->data = e;
    Q.rear->next = s;
    Q.rear = s;
    s->next = NULL;
}
//入队操作

bool DeQueue(Queue &Q,ElemType &e)
{
    if(QueueEmpty(Q))
    {
        cout << "This Queue is empty"<<endl;
        return false;
    }
    LNode *p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p)
    {
        Q.rear = Q.front;
    }
    free(p);
    return true;
}
//出队操作

bool CreateQueue(Queue &Q, int n, ElemType *series) //n为个数,series 为一个数组
{
    for (int i = 0; i < n; i++)
    {
        EnQueue(Q,series[i]);
    }
}
//建立一个队列的函数