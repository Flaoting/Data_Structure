#include <iostream>
#include "1_first.cpp"
using namespace std;

/*
设元素值为整型的线性表L，分别采用顺序结构和链式结构存储，编写函数，实现线性表的就地逆置（书P31 4）。
*/

bool ReverseList(SqeList *L)
{
    int temp=0;
    for (int i = 0; i < L->length / 2 ; i ++)
    {
        temp = L->pData[i];
        L->pData[i] = L->pData[L->length-i-1];
        L->pData[L->length-i-1] = temp;
    }
    return true;
}

int main()
{
    SqeList L;
    int i,e,temp,location=-1;
    InitList(&L);
    CreateList(&L);
    ListTraverse(L);
    ReverseList(&L);
    ListTraverse(L);
    return 0;
    
}