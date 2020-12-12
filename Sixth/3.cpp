/*3. 编写函数，对二叉链表结构的二叉树，求宽度。（书P94 4）*/
#include "BinaryTree.h"
#include <iostream>
using namespace std;
/*
int CaculateWidthOfBinaryTree(BiTree &BT)
{
    BiTNode *p = BT;
    queue <BiTNode*> Q;
    Q.push(BT);
    Q.push(NULL);
    
    int max_cnt = -1;
    int cnt = 1;
    bool flag = false;

    while(!Q.empty())
    {
        p = Q.front();
        Q.pop();
        if(p == NULL)
        {
            if(flag)
            {
                break;
            }
            max_cnt = max(max_cnt,cnt);
            cnt = 0;
            Q.push(NULL);
            flag = true;
            continue;
        }
        flag = false;
        if(p->lchild != NULL)
        {
            cnt ++;
            Q.push(p->lchild);
        }
        if(p->rchild != NULL)
        {
            cnt ++;
            Q.push(p->rchild);
        }
    }
    return max_cnt;
}
*/
int main()
{
    test();
    return 0;
}