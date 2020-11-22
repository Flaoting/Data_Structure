#include "1_second.cpp"
/*
设元素值为整型的线性表L，分别采用顺序结构和链式结构存储，编写函数，实现线性表的就地逆置（书P31 4）。
*/

bool ReverseList(LinkList &L)
{
    if (ListLength(L)<=1 || L==NULL) return true;
    LinkList S=L;
    LNode *p = L->next,*q = p ;
    S->next = NULL;
    while (p)
    {
        q = p->next;
        p->next = S->next;
        S->next = p;
        p = q;
    }
    return true;
}
int main()
{ 
    LinkList L=NULL;
    int e =999,temp = -111; 
    InitList(L);
    CreateList (L,8);
    ListTraverse (L);
    ReverseList(L);
    ListTraverse (L);
    DestroyList(L);
    ReverseList(L);
    ListTraverse(L);
    return 0;
}