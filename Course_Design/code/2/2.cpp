#define MAX_SIZE 50
#include <iostream>
using namespace std;

typedef struct point
{
    int x, y, dir; //dir为下一可走方块的方位号
}point;

typedef struct map
{
    int row, col; // 长和宽度各有多少
    char map[MAX_SIZE][MAX_SIZE];
    bool flag[MAX_SIZE][MAX_SIZE];

}Graph;

typedef struct stk 
{
    point data[300];
    int top;
}Stk;

void initGraph(Graph& G)
{
    G.col = 0;
    G.row = 0;
    return;
}

void show(Graph& G)
{
    for (int i = 1; i <= G.row; i++)
    {
        for (int j = 1; j <= G.col; j++)
        {
            cout << G.map[i][j] << " ";
        }
        cout << endl;
    }
}

void print(Graph& G) 
{
    for (int i = 1; i <= G.row; i++)
    {
        for (int j = 1; j <= G.col; j++)
        {
            cout << G.map[i][j] << " ";
        }
        cout << endl;
    }
}
void read(Graph& G)
{
    FILE* stream;
    freopen_s(&stream,"graph.txt","r",stdin);

    cin >> G.row >> G.col;
    //cout << G.row << G.col <<endl;

    for (int i = 1; i <= G.row; i++)
    {
        for (int j = 1; j <= G.col; j++)
        {
            cin >> G.map[i][j];
            G.flag[i][j] = false;
        }
    }
}

void findPath(Graph& G, int x, int y, int dx, int dy)
{
    int i, j, dir, find,cnt = 0;
    Stk S;
    S.top = -1;
    S.top++;    //起点进栈
    S.data[S.top].x = x;
    S.data[S.top].y = y;
    S.data[S.top].dir = -1;

    G.map[x][y] = '2';
    while (S.top > -1)
    {
        i = S.data[S.top].x;
        //cout << i << endl;
        j = S.data[S.top].y;
        dir = S.data[S.top].dir;
        if (i == dx && j == dy) 
        {
            cnt++;
            cout << "-------------------------------------------------------" << endl;
            cout << "The "<<cnt <<"th trail is : "<< endl;
            show(G);
            cout << "-------------------------------------------------------" << endl;
        }
        find = 0;
        while (dir < 4 && find == 0) 
        {
            dir++;
            switch (dir)
            {
            case 0:
                i = S.data[S.top].x - 1;
                j = S.data[S.top].y;
                break;
            case 1:
                i = S.data[S.top].x;
                j = S.data[S.top].y + 1;
                break;
            case 2:
                i = S.data[S.top].x + 1;
                j = S.data[S.top].y;
                break;
            case 3:
                i = S.data[S.top].x;
                j = S.data[S.top].y - 1;
                break;
            }
            if (i<1 || j<1 || i>G.row || j>G.col) 
            {
                continue;
            }
            if (G.map[i][j] == '0')
            {
                find = 1;
            }
        }

        if (find == 1) 
        {
            S.data[S.top].dir = dir;
            S.top++;
            S.data[S.top].x = i;
            S.data[S.top].y = j;
            S.data[S.top].dir = -1;
            G.map[i][j] = '2';
            //cout << "i = " << i << " j = " << j << endl;
        }
        else 
        {
            //cout << S.data[S.top].x <<" "<< S.data[S.top].y << endl;
            G.map[S.data[S.top].x][S.data[S.top].y] = '0';
            S.top--;
        }
    }
}

int main()
{
    Graph G;
    initGraph(G);
    read(G);
    print(G);
    findPath(G, 1, 1, 25, 25);
    return 0;
}