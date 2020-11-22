//用一个栈解决八皇后问题

typedef struct Queen //定义皇后这个结构体
{
    int row;    //皇后的行数
    int col;    //皇后的列数

}Queen;

#ifndef ElemType
#define ElemType Queen

#include "Stack.h"
#include <cmath>
using namespace std;

void print(ElemType e)
{
    cout <<"\tQueen's row is "<<e.row<<" and col is "<<e.col<<endl;
}
//打印皇后状态的函数

void printQueen(Stack S,int ans)
{
    cout << "Now we will show the "<<ans<< " answers."<<endl;
    StackTraverse(S);
}

bool JudgeConfliction(Queen newQueen, Stack QueenStack)
{
    ElemType *pCurQueen;

    int x1 = newQueen.col, y1 = newQueen.row;
    pCurQueen = QueenStack.pBase;
    bool tag = false;
    
    while(pCurQueen<QueenStack.pTop)
    {
        register int x2 = pCurQueen->col, y2 = pCurQueen->row;
        if(x1 == x2)
        {
            tag = true;
            break;
            //发生冲突,tag置为true,循环结束
        }
        if(y1 == y2)
        {
            tag = true;
            break;
            //发生冲突,tag置为true,循环结束
        }
        if(abs(x1-x2) == abs(y1-y2))
        {
            tag = true;
            break;
        }
        pCurQueen ++;
    }
    return tag;
}
//判断皇后的冲突，如果冲突就返回true，否则返回false
int main()
{
    int number;
    cout << "Please input the number of queens you want to make :  ";
    cin >> number;
    
    Stack QueenStack;
    Queen curQueen;
    InitStack(QueenStack);
    int ans = 0;
    curQueen.row = 1;
    curQueen.col = 1;
    Push(QueenStack,curQueen);
    //把第一个皇后压栈

    curQueen.row = 2;

    while(curQueen.col <= number && curQueen.row <= number)
    {
        bool tag = true; //默认是冲突的状态
        while(curQueen.col <= number)
        {
            tag = JudgeConfliction(curQueen,QueenStack);
            if(!tag)
            {
                break;  //在这一行找到了合适的列
            }
            curQueen.col += 1;
        }
        
        if(!tag)
        {
            Push(QueenStack,curQueen); //推入当前的皇后，放下一行的
            curQueen.row += 1;
            curQueen.col = 1;
            
            if(curQueen.row > number) //达到搜索终点
            {
                ans++;
                printQueen(QueenStack,ans);
                Pop(QueenStack,curQueen);
                curQueen.col+=1;
                while(curQueen.col > number && !StackEmpty(QueenStack))
                {
                    Pop(QueenStack,curQueen);
                    curQueen.col+=1;
                }
            }
        }
        else
        {
            Pop(QueenStack,curQueen);
            curQueen.col+=1;
            
            while(curQueen.col > number && !StackEmpty(QueenStack))
            {
                Pop(QueenStack,curQueen);
                curQueen.col+=1;
            }
        }

    }
    cout << "The number of ans is " << ans << endl;
    DestroyStack(QueenStack);
    return 0;
}
#endif