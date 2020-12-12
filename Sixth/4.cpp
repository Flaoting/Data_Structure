/*4. 编写函数，对一棵以孩子-兄弟链表表示的树，输出第i层的所有元素。*/
#include <iostream>
#include <string>
#include <queue>
#include <malloc.h>
#include <fstream>
using namespace std;

#define TElemType char

typedef struct TreeNode
{
    TElemType data;
    struct TreeNode *firstchild, *nextBrother; 
}CBTreeNode, *CBTree;

void CreateCBTree(CBTree &T)
{
    T = (CBTreeNode*)malloc(sizeof(CBTreeNode));
    T->data = 0;
    T->firstchild = NULL;
    T->nextBrother = NULL;
    cout << "YES"<<endl;
    return;
}
//创建一课孩子兄弟表示法表示的树

//pos 为一个01串，可以表示寻找结点的过程，0表示向右，1表示向下
bool InsertNode(CBTree &T, char data, string pos)      //pos is a series of 01
{
    if(T == NULL)
    {
        cout << "You can't insert anything to NULL Tree"<<endl;
        return false;
    }

    int count = pos.length();
    
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    
    node->data = data;
    node->firstchild = NULL;
    node->nextBrother = NULL;

    TreeNode *p = (TreeNode*)malloc(sizeof(TreeNode));
    p->firstchild = T;
    int i=0;
    char temp;

    while(count > 0 && p != NULL)
    {
        temp = pos[i];
        if(temp == '0')
        {
            p = p->nextBrother;
        }
        else if(temp == '1')
        {
            p = p->firstchild;
        }
        else
        {
            cout << "Your pos is invalid, the string pos is "<< pos<<endl;
            return false;
        }
        count --;
        i++;
    }

    if(p == NULL)
    {
        cout << "Insert position is invalid, the string pos is "<< pos <<" and the count is "<< count <<endl;
        return false;
    }

    CBTreeNode *q = p->firstchild;
    
    if(q == NULL)
    {
        p->firstchild = node;
    }
    else 
    {
        while(q->nextBrother != NULL)
        {
            q = q->nextBrother ;
        }
        q->nextBrother = node;
    }

    return true;
}
//对树进行结点的插入

void readTree(CBTree &T, string FileName)
{
    int N=0;
    char data;
    string pos;
    fstream file(FileName.c_str(), ios::in);
    if(!file)
    {
        cout << "file can't be opened !"<<endl;
        exit(0);
    }

    file >> N; //多少个结点，包括根结点
    file.ignore();
    file >> T->data;
    cout << T->data<<endl;
    char a[2];
    for(int i = 1; i < N; i++ )
    {
        file.ignore();
        file.read((char*)&a,1);
        data = a[0];
        file >> pos;
        InsertNode(T, data, pos);
        cout << data << " " << pos<<endl;
    }
    return;
}
//从文件中读入树的数据

void r_display(CBTreeNode *node, int gap)
{
    if(node == NULL)
    {
        return;
    }
    for(int i = 0; i < gap; i++)
    {
        cout << "-";
    }
    cout << node->data << endl;
    CBTreeNode *child = node->firstchild;
    r_display(child, gap+4);

    CBTreeNode *brother = node->nextBrother;
    r_display(brother, gap);
}
//递归打印树

void Display(CBTree &T)
{
    if(T == NULL)
    {
        cout << "null" <<endl;
    }
    else 
    {
        r_display(T,0);
    }
}

void printNode(CBTreeNode *node)
{
    cout << node->data << " ";
}
void PrintTH(CBTree &T,int i)
{
    CBTreeNode *p = T, *q;
    queue <CBTreeNode*> Q;      //搞一个队列
    bool flag = false;
    int cnt = 0;
    i --;
    Q.push(p);
    Q.push(NULL);
    while(!Q.empty())
    {
        if(cnt == i)
        {
            while(!Q.empty())
            {
                q = Q.front();
                Q.pop();
                if(q != NULL)
                {
                    printNode(q);
                }
            }
            break;
        }
        p = Q.front();
        Q.pop();
        if(p == NULL)
        {
            if(flag)
            {
                cout << "Floating TIP   WARNING OVERFLOW" <<endl;
                break;
            }
            cnt ++;
            Q.push(NULL);
            flag = true;
            continue;
        }
        flag = false;
        if(p->firstchild != NULL)
        {
            q = p->firstchild;
            do
            {
                Q.push(q);
                q = q->nextBrother;
            }while(q!=NULL);
        }

    }

}
//打印第i层

int main()
{
    CBTree T;
    CreateCBTree(T);
    readTree(T,"4.txt");
    
    Display(T);
    PrintTH(T,3);
    // char p;
    // fstream file("4.txt",ios::in);
    // while (!file.eof())
    // {
    //     file >> p;
    //     cout << p <<endl;
    // }
    return 0;
}