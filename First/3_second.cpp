/*3．设线性表L，元素值为整型的且存在相同值，分别采用顺序结构和链式结构存储，编写函数，利用原空间，删除重复的元素值。*/
#include <iostream>
#include "1_second.cpp"
using namespace std;
bool DeleteRepeteList(LinkList &L)
{
    int length = ListLength(L) ;
    if (length == 0 || length == 1)
    {
        return true;
        //0 或者 1,直接返回排序成功
    }
    LNode *p = L->next, *q = p,*r = p;
    while (p)
    {
        r = p;
        q = p->next;
        while(q!=NULL)
        {
            if (q->data == p->data)
            {
                r->next = q->next;
                free(q);
                q = r;

            }
            r = q;
            q = q->next;
        }

        p  = p->next;
    }
    return true;
}
int main()
{
    LinkList L=NULL;
    int e =999,temp = -111; 
    InitList(L);
    CreateList (L,15);
    ListTraverse (L);
    DeleteRepeteList(L);
    ListTraverse(L);
}


