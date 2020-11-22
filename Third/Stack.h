/*
这是栈的头文件，调用时注意 宏定义ElemType
1.InitStack
2.DestroyStack
3.ClearStack
4.GetTop
5.Push
6.Pop
7.CreateStack
*/
#include <cstdlib>
#include <iostream>
using namespace std;

const int STACKINITSIZE  = 256;
const int STACKINCREMENT = 128;
extern void print(ElemType e);

typedef struct Stack
{
    ElemType *pBase;
    ElemType *pTop;
    int stacksize;
}Stack;

bool InitStack(Stack &S)
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

bool DestroyStack(Stack &S)
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

bool ClearStack(Stack &S)
{
    S.pTop = S.pBase;   //直接让栈顶指向栈底部
    return true;
}
//清空栈中元素

bool StackEmpty(const Stack &S)
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

int StackLength(const Stack &S)
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

bool StackTraverse(const Stack &S)
{
    ElemType *p = S.pBase;
    cout << "Now we will show the traversed result !"<<endl;
    while(p != S.pTop)
    {
        print(*p);
        cout << " ";
        p++;
    }
    cout << endl;
    return true;
}
//从栈底向栈顶遍历栈中的所有元素,print为打印当前的ElemType的函数

bool GetTop(Stack &S, ElemType &e)
{
    if (S.pTop == S.pBase) return false;
    e = *(S.pTop - 1);
    return true;
}
//取出栈顶的元素

bool Push(Stack &S, ElemType e)
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

bool Pop(Stack &S, ElemType &e)
{
    if (S.pTop <= S.pBase)
    {
        return false;
    }
    e = *(S.pTop - 1);
    S.pTop--;
    return true;
}
//弹栈操作

bool CreateStack(Stack &S, int n, ElemType *Elem)  //传入一个有n个Elem类型的数组
{
    for (int i=0; i<n; i++)
    {
        Push(S,Elem[i]);
    }
    return true;
}   
//初始化建栈


