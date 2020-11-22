/*1．编程实现书P32   ADT Stack 基本操作9个，用顺序存储结构实现；*/
#include <iostream> 
#include <cstdlib>
using namespace std;
#ifndef ElemType
#define ElemType int
const int STACKINITSIZE  = 256;
const int STACKINCREMENT = 128;

typedef struct SeqStack
{
    ElemType *pBase;
    ElemType *pTop;
    int stacksize;
}SeqStack;

void print(ElemType e)

{
    cout << e;
}
//打印当前元素

bool InitStack(SeqStack &S)
{
    S.pBase = (ElemType *)malloc(STACKINITSIZE * sizeof (ElemType));
    if (S.pBase == NULL)
    {
        exit(0);
    }
    S.pTop = S.pBase;
    S.stacksize = STACKINITSIZE;
    return true;
}
//栈的初始化

bool DestroyStack(SeqStack &S)
{
    if (S.pBase != NULL)
    {
        free(S.pBase);
        S.pBase = NULL;
    }
    S.pTop = NULL;
    S.stacksize = 0;
    return true;
}
//栈的销毁

bool ClearStack(SeqStack &S)
{
    S.pTop = S.pBase;   //直接让栈顶指向栈底部
    return true;
}
//清空栈中元素

bool StackEmpty(const SeqStack &S)
{
    if(S.pBase == S.pTop)
    {
        return true;
    } 
    else
    {
        return false;
    }
}
//判断栈是否为空栈

int StackLength(const SeqStack &S)
{
    ElemType *p = S.pBase;
    int cnt=0;
    while(p!=S.pTop)
    {
        p++;
        cnt++;
    }
    return cnt;
}
//计算栈中元素的长度

bool StackTraverse(const SeqStack &S)
{
    ElemType *p = S.pBase;
    cout << "The Traverse result is : ";
    while(p != S.pTop)
    {
        print(*p);
        cout << " ";
        p++;
    }
    cout << endl;
    return true;
}
//从栈底向栈顶遍历所有元素

bool GetTop(SeqStack &S, ElemType &e)
{
    if (S.pTop == S.pBase) return false;
    e = *(S.pTop - 1);
    return true;
}
//取出栈顶的元素

bool Push(SeqStack &S, ElemType e)
{
    if (S.pTop - S.pBase >= S.stacksize)
    {
        S.pBase = (ElemType *)realloc(S.pBase,(S.stacksize+STACKINCREMENT)*(sizeof(ElemType)));
        if (S.pBase == NULL)
        {
            cout << "Memory is overflowed !"<<endl;
            exit(0);
        }
        S.pTop = S.pBase+S.stacksize;
        S.stacksize += STACKINCREMENT;    
    }
    *S.pTop = e;
    S.pTop++;
    return true;
}
//压栈操作

bool Pop(SeqStack &S, ElemType &e)
{
    if (S.pTop <= S.pBase)
    {
        return false;
    }
    e=*(S.pTop - 1);
    S.pTop--;
    return true;
}
//弹栈操作

bool CreateStack(SeqStack &S, int n, ElemType *Elem)  //传入一个有n个数字的数组
{
    for (int i=0; i<n; i++)
    {
        Push(S,Elem[i]);
    }
    return true;
}   
//初始化建栈

bool PrintStack(SeqStack S)
{
    if (S.pBase == S.pTop)
    {  
       cout << "This Satck is empty"<<endl;
       return true; 
    }
    cout << "The Stack From Base To Top Is :";
    int *p;
    p = S.pBase;
    while (p<S.pTop)
    {
        cout << *p << " ";
        p++;
    }
    cout << endl;
    return true;
}
//打印一个栈中的元素
int main()
{
    SeqStack S;
    int e = -1;
    int a[50]={45,454,148,35,1,34,899,1565,5448,65,-564,-1545121};
    
    InitStack(S);
    
    for (int i=0;i<=5;i++)
    {
        Push(S,a[i]);
    }

    PrintStack(S);
    cout << "Now e is "<<e<<endl;
    Pop(S,e);
    PrintStack(S);
    cout << "Now e is "<<e<<endl;
    //ClearStack(S);
    //PrintStack(S);
    StackTraverse(S);
    e = -1;
    cout << "Now e is "<<e<<endl;
    GetTop(S,e);
    cout << "Now e is "<<e<<endl;
    if(StackEmpty(S))
    {
        cout << "The stack is empty "<<endl;
    }
    cout << StackLength(S)<<endl;
    ClearStack(S);
    if(StackEmpty(S))
    {
        cout << "Yes, The stack is empty !"<<endl;
    }
    cout << StackLength(S)<<endl;
    return 0;
}
#endif