#include <iostream>
#include <fstream>
using namespace std;
#define INF 1e9+7
int G[1005][1005];
int n, m, s;
int path[1005], dis[1005];
bool flag[1005];

void read()
{
    fstream file("2.txt",ios::in);
    file >> n >> m >> s;
    int u, v, w;
    
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            G[i][j] = INF;
        }
    }
    
    for(int i = 1; i <= m; i++)
    {
        file >> u >> v >> w;
        G[u][v] = w;
    }
    file.close();
    return ;
}

void showGraph()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            cout << G[i][j]<< " ";
        }
        cout << " " <<endl;
    }
    return ;
}

void Dijkstra(int s)
{
    for(int i = 1; i <= n; i++)
    {
        path[i] = s;
        dis[i] = G[s][i];
        if(i == s)
        {
            dis[i] = 0;         //初始点到自己的距离为0
        }
    }

    flag[s] = true;
    int min_index;
    for(int cnt = 2; cnt <= n; cnt ++) //循环n-1次,把所有的点都拓展进来
    {
        min_index = -1;
        for(int i = 1; i <= n; i++) //选出路径最短的点
        {
            if(!flag[i])
            {
                if(min_index == -1)
                {
                    min_index = i;
                }
                else if(dis[i] < dis[min_index])
                {
                    min_index = i;
                }
            }
        }

        flag[min_index] = true;
        for(int i = 1; i <= n; i++)
        {
            if(!flag[i])
            {
                if(dis[i] > G[min_index][i] + dis[min_index])
                {
                    dis[i] = G[min_index][i] + dis[min_index];
                    path[i] = min_index;
                }
            }
        }
    }
    return ;
}
void print()
{
    for(int i = 1; i <= n; i++)
    {
        cout << dis[i] << " ";
    }
    return ;
}
int main()
{
    read();
    Dijkstra(s);
    print();
    return 0;
}

