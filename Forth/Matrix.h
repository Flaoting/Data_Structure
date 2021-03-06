#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

#define INITSIZE 256
#define INCRESIZE 128
#define MAXSIZE 512

#define ElemType int

typedef struct
{
    int i, j;   //矩阵行列标号均从1开始
    ElemType value;
}Triple;

typedef struct
{
    Triple *arr;
    int Rows, Cols, Nums;  //行数为5，标号为1 - 5
    int MatrixSize;
}SeqMatrix;

bool operator < (const Triple &a, const Triple &b)
{
    if(a.i < b.i)
    {
        return true;
    } 
    
    else if(a.i == b.i&& a.j < b.j) 
    {
        return true;
    }

    else
    {
         return false;
    }
}

bool operator == (const Triple &a, const Triple &b)
{
    if ((a.i == b.i)&&(a.j == b.j))
    {
        return true;
    }
    else 
    {
        return false;
    }
}

bool InitMatrix(SeqMatrix &M)
{
    M.arr = (Triple*)malloc(sizeof(Triple)*INITSIZE);
    if (M.arr == NULL)
    {
        cout << "Memory is overflow !"<<endl;
        exit (0);
    }
    M.MatrixSize = INITSIZE;
    M.Rows = 0;
    M.Cols = 0;
    M.Nums = 0;
    for (int i = 0; i < INITSIZE; i++)
    {
        M.arr[i].i = -1;
        M.arr[i].j = -1;
        M.arr[i].value = -1; 
    }
    return true;
}
//初始化矩阵

bool CreateMatrix(SeqMatrix &M, int row, int col, int n, const int *rows, const int *cols)
//行数，列数，元素数，行元素数组，列元素数组
{
    if (M.arr == NULL)
    {
        return false;
    }
    for (int i = 0; i < n; i++)
    {
        M.arr[i].i = rows[i];
        M.arr[i].j = cols[i];
        M.arr[i].value = i+1; 
        M.Nums ++;
    }
    M.Rows = row;
    M.Cols = col;
    return true;
}
//创建矩阵

bool DestroyMatrix(SeqMatrix &M)
{
    M.Rows = 0;
    M.Cols = 0;
    M.Nums = 0;

    if(M.arr != NULL)
    {
        free(M.arr);
        M.arr = NULL;
    }

    return true;
}
//销毁矩阵

void PrintMatrix(SeqMatrix &M)
{
    //cout << "[ ";
    int row = 1, col = 1;
    Triple *p=M.arr;
    int num = 0;
    cout << endl;
    while(row <= M.Rows)
    {
        if(p->i == row)
        {
            while(col <= M.Cols)
            {
                if((p->j == col)&&(p->i == row))
                {
                    cout << setw(4) << p->value;
                    p++;
                    num ++;
                }
                else
                {
                    cout << setw(4) << "0";
                }
                col++;
            }
            cout << endl;
        }
        else 
        {
            while (col <= M.Cols)
            {
                cout << setw(4) << "0";
                col ++;
            }
            cout << endl;
        }
        col = 1;
        row ++;
        //cout << "now row is "<< row <<" and p->i = "<<p->i<<" and num is "<<num<<endl;
    }
    cout <<endl;
    return;
}
//打印矩阵

void CopyMatrix(const SeqMatrix &A, SeqMatrix &B)
{
    B.Cols = A.Cols;
    B.Rows = A.Rows;
    B.Nums = A.Nums;
    while(B.MatrixSize < A.MatrixSize)
    {
        B.arr = (Triple*)realloc(B.arr,sizeof(Triple)*(B.MatrixSize+INCRESIZE));
        B.MatrixSize += INCRESIZE;
    }
    for (int i = 0; i < A.Nums; i++)
    {
        B.arr[i].i = A.arr[i].i;
        B.arr[i].j = A.arr[i].j;
        B.arr[i].value = A.arr[i].value;
    }
}
//复制矩阵

bool AddMatrix(const SeqMatrix &A, const SeqMatrix &B, SeqMatrix &C)
{
    if ((A.Cols != B.Cols)||(A.Rows != B.Rows))
    {
        return false;
    }
    C.Cols = A.Cols;
    C.Rows = A.Rows;
    while((C.MatrixSize < A.MatrixSize)||(C.MatrixSize < B.MatrixSize) )
    {
        C.arr = (Triple*)realloc(C.arr,sizeof(Triple)*(C.MatrixSize+INCRESIZE));
        C.MatrixSize += INCRESIZE;
    }

    int p = 0, q = 0, w = 0;    //指向p和q的下标指针
    while(p < A.Nums || q < B.Nums)
    {
        //如果有一个跑完了，另一个直接复制过去即可
        if(p == A.Nums)
        {
            while(q < B.Nums)
            {
                C.arr[w].value = B.arr[p].value;
                C.arr[w].i = B.arr[q].i;
                C.arr[w].j = B.arr[q].j;
                w++;
                q++;
                C.Nums++;
            }
            break;
        }
        if(q == B.Nums)
        {
            while(p < A.Nums)
            {
                C.arr[w].value = A.arr[p].value;
                C.arr[w].i = A.arr[p].i;
                C.arr[w].j = A.arr[p].j;
                w++;
                p++;
                C.Nums++;
            }
            cout << "YES"<<endl;
            break;
        }
        
        //如果当前两个下标之指针指向的位置坐标相同，那么数值直接相加
        if((A.arr[p] == B.arr[q]) && (A.arr[p].i != -1))
        {
            C.arr[w].value = A.arr[p].value + B.arr[q].value;
            C.arr[w].i = A.arr[p].i;
            C.arr[w].j = A.arr[p].j;
            // cout << p << " " << q << " " << w <<endl;
            // cout << C.arr[w].value<<endl;
            p++;
            q++;
        }
        else if(A.arr[p] < B.arr[q])
        {
            C.arr[w].value = A.arr[p].value;
            C.arr[w].i = A.arr[p].i;
            C.arr[w].j = A.arr[p].j;
            // cout << p << " " << q << " " << w <<endl;
            // cout << C.arr[w].value<<endl;
            p++;
        }
        else
        {
            C.arr[w].value = B.arr[q].value;
            C.arr[w].i = B.arr[q].i;
            C.arr[w].j = B.arr[q].j;
            q++;
        }
        w ++;
        C.Nums ++;
        if(C.Nums >= C.MatrixSize)
        {
            C.arr = (Triple*)realloc(C.arr,sizeof(Triple)*(C.MatrixSize+INCRESIZE));
            C.MatrixSize += INCRESIZE;
        }

    }
    return true;
}

bool Column_order_traversal_transpose(SeqMatrix &A, SeqMatrix &B)
{
    if (A.Nums == 0)
    {
        return true; //当A中有0个元素，那么直接返回true,即所有元素都为0 
    }
    B.Cols = A.Rows;
    B.Rows = A.Cols;
    B.Nums = A.Nums;
    int q = 0;
    for(int i = 1; i <= A.Cols; i++)
    {
        for (int p = 0; p<A.Nums; p++)
        {
            if (A.arr[p].j == i)
            {
                B.arr[q].i = A.arr[p].j;
                B.arr[q].j = A.arr[p].i;
                B.arr[q].value = A.arr[p].value;
                q++;
            }
        }
    }

    return true;
}
//列序遍历转置

#endif