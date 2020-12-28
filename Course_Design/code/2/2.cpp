/*2、迷宫问题（必做）（栈与队列）
[问题描述]
利用栈操作实现迷宫问题求解。
[基本要求]
（1）从文件中读取数据，生成模拟迷宫地图，不少于20行20列。
（2）给出任意入口和出口，显示输出迷宫路线。
*/
#define MAX_SIZE 50
#include <iostream>
#include <stack>
using namespace std;

typedef struct node
{
    int x,y;
    struct node *pre;
}node;

typedef struct map
{
    int row,col; // 长和宽度各有多少
    char map[MAX_SIZE][MAX_SIZE];
    bool flag[MAX_SIZE][MAX_SIZE];

}Graph;

void initGraph(Graph &G)
{
    G.col = 0;
    G.row = 0;
    for(int i = 1; i < G.row ; i++)
    {
        for(int j = 1; j <= G.col; j++)
        {
            G.map[i][j] = -1;
            G.flag[i][j] = false;
        }
    }
    return ;
}

void show(Graph &G)
{
    for(int i = 1; i < G.row ; i++)
    {
        for(int j = 1; j <= G.col; j++)
        {
            if(!G.flag[i][j])
            {
                cout << G.map[i][j]<<" ";
            }
            else 
            {
                cout << "2" << " ";
            }
        }
        cout << endl;
    }   
}

void read(Graph &G)
{
    freopen ("graph.txt","r",stdin);

    cin >> G.row >> G.col;
    //cout << G.row << G.col <<endl;

    for(int i = 1; i <= G.row ; i++)
    {
        for(int j = 1; j <= G.col; j++)
        {
            cin >> G.map[i][j];
        }
    }
}

void pre_operate(Graph &G,stack <node> S)
{
    stack <node> Q;
    node p;
    while(!S.empty())
    {
        p = S.top();
        Q.push(p);
        S.pop();
        G.flag[p.x][p.y] = false;
    }
}

void findPath(Graph &G, int x, int y, int dx, int dy)
{
    node p, q, object;
    stack <node> S;
    bool flag = false;
    p.x = x;
    p.y = y;
    object.x = dx;
    object.y = dy;

    S.push(p);

    while(!S.empty())
    {
        q = S.top();
        S.pop();
        cout << q.x <<" " <<q.y <<endl;
        flag = false;
        
        if(q.x == object.x && q.y == object.y)
        {
            pre_operate(G,S);
            show(G);
        }

        if(q.x - 1 > 0 && !G.flag[q.x-1][q.y] && G.map[q.x-1][q.y] =='0')
        {
            p.x = q.x - 1;
            p.y = q.y;
            S.push(p);
            flag = true;
        }

        // cout << "!G.flag[q.x+1][q.y] = "<<!G.flag[q.x+1][q.y]<<endl;
        // cout << "G.map[q.x + 1][q.y] = "<<G.map[q.x + 1][q.y] <<endl;

        if(q.x + 1 <= G.col && !G.flag[q.x+1][q.y] && G.map[q.x + 1][q.y] =='0')
        {
            p.x = q.x + 1;
            p.y = q.y;
            S.push(p);
            flag = true;
        }

        if(q.y - 1 > 0 && !G.flag[q.x][q.y-1] && G.map[q.x][q.y-1] =='0')
        {
            p.x = q.x;
            p.y = q.y - 1;

            S.push(p);
            flag = true;
        }

        if(q.y + 1 <= G.row && !G.flag[q.x][q.y+1] && G.map[q.x][q.y+1] =='0')
        {
            p.x = q.x;
            p.y = q.y + 1;
            S.push(p);
            flag = true;
        }
        if(flag)
        {
            //cout << q.x << " ..." << q.y <<endl; 
            G.flag[q.x][q.y] = true;
        }
    }

}

int main()
{
    Graph G;
    initGraph(G);
    read(G);
    //show(G);
    findPath(G,1,1,25,25);
}