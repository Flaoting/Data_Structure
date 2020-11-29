/*假设以二维数组g(1...m,1...n),表示一个图像区域，g[i,j]表示该区域中点(i,j)
所具有的颜色，其值为从0到k的整数。编写算法置换点(i0,j0)所在区域的颜色。约定和
(i0,j0)同色的上下左右的邻接点为同色区域的点。*/
#include <iostream>
#include <fstream>

typedef struct Point
{
    int x; 
    int y;
}Point;

#define ElemType Point

#include "Stack.h"

using namespace std;

const int M = 10;
const int N = 10;
char map[M+5][N+5];

void print(ElemType e)
{
    cout << e.x <<" "<< e.y <<endl;
}

void readMap( )
{
    fstream file("5.txt",ios::in);

    for (int i = 1; i <= M; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            file >> map[i][j];
        }
    }
    file.close();

    return;
}

void printMap()
{
    for (int i = 1; i<=M; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void ChangeColorWithRecursion(char toColor, int x, int y)
{
    cout << x << "  "<< y << endl;
    if(x < 1 || x > M || y < 1 || y > N)        //在查找的范围之外了
    {
        return ;
    }
    char color = map[x][y];
    if(map[x][y] == toColor)
    {
        return;
    }
    map[x][y] = toColor;
    if((x+1 <= M) && (map[x+1][y] == color))
    {
        ChangeColorWithRecursion(toColor, x+1, y);
    }
    
    if((x-1 >= 1) && map[x-1][y] == color)
    {
        ChangeColorWithRecursion(toColor, x-1, y);
    }
    
    if((y+1<=N) && map[x][y+1] == color)
    {
        ChangeColorWithRecursion(toColor, x, y+1);
    }
    
    if((y-1>=1) && map[x][y-1] == color)
    {
        ChangeColorWithRecursion(toColor, x, y-1);
    }
    cout << "now x = "<< x <<" and y = "<< y<<endl<<endl;
    printMap();
    cout << endl<<endl;
    return;
}

void ChangeColorWithStack(char toColor, int x, int y)
{
    Stack S;
    InitStack(S);
    char oldColor = map[x][y];
    Point p,q;
    p.x = x;
    p.y = y;
    map[x][y] = toColor;    //先染色，后压栈
    Push(S,p);
    while (!StackEmpty(S))
    {
        Pop(S,q);
        //print(q);
        //printMap();
        if((q.x - 1 >= 1)&&map[q.x - 1][q.y] == oldColor)
        {
            map[q.x - 1][q.y] = toColor;
            p.x = q.x - 1;
            p.y = q.y;
            Push(S,p);
        }
        if((q.x + 1 <= M) && map[q.x + 1][q.y] == oldColor)
        {
            map[q.x + 1][q.y] = toColor;
            p.x = q.x + 1;
            p.y = q.y;
            Push(S,p);
        }
        if((q.y - 1 >= 1)&&map[q.x][q.y - 1] == oldColor)
        {
            p.x = q.x;
            p.y = q.y - 1;
            map[q.x][q.y - 1] = toColor;
            Push(S,p);
        }
        if((q.y + 1 <= M)&&map[q.x][q.y + 1] == oldColor)
        {
            p.x = q.x;
            p.y = q.y + 1;
            map[q.x][q.y + 1] = toColor;
            Push(S,p);
        }
    }
    return ;
}

int main ()
{
    readMap();
    printMap();
    //ChangeColorWithRecursion('2',1,3);
    cout <<endl;
    ChangeColorWithStack('2',6,10);
    printMap();
    return 0;
}
