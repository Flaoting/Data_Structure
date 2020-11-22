/*3．设线性表L，元素值为整型的且存在相同值，分别采用顺序结构和链式结构存储，编写函数，利用原空间，删除重复的元素值。*/
#include <iostream>
#include "1_first.cpp"  //引入线性结构的表
using namespace std;
bool DeleteRepeteList(SqeList *L)
{
    if (L->length == 0 || L->length == 1) return true;//有零个或者一个元素，那么不会有重复的数据
    int p1=1,p2=1;
    bool flag=false;
    while (p2!=L->length)
    {
        flag = false;
        for (int i = 0; i < p1; i ++)
        {
            if(L->pData[i] == L->pData[p2])
            {
                flag = 1; //找到相等的了
                break;
            }
        }
        if(flag)
        {
            p2++;
            
            continue;
        }
        else 
        {
            L->pData[p1] = L->pData[p2];
            p1 ++;
            p2 ++;
            continue;
        }
    }
    L->length = p1;
    return true;
}

int main()
{
    SqeList L;
    int i,e,temp,location=-1;
    InitList(&L);
    CreateList(&L);
    ListTraverse(L);
    DeleteRepeteList(&L);
    ListTraverse(L);
}


