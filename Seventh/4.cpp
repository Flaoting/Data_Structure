#include <iostream>
#include <string.h>
using namespace std;
#define INF 22222222
int G[1005][1005];
int n,m;
void read()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            G[i][j] = INF;
        }
    }
    int u,v,w;

    for(int i = 1; i <= m; i++)
    {
        cin >> u >> v >> w;
        G[u][v] = w;
        G[v][u] = w;
    }
}
struct node
{
    int lowcost;    //最小的权
    int from;   //从哪个点来的
};

struct node help[1005];

int prim()
{
    long long sum = 0;
    help[1].lowcost = -2;
    for(int i = 2; i <= n; i++)
    {
        help[i].from = 1;
        help[i].lowcost = G[1][i];
    }

    int min_index; //当前最小lowcost的下标

    for(int i = 2; i <= n; i++)
    {
        min_index = -1;
        for(int j = 2; j <= n; j++)
        {
            if(help[j].lowcost != -2 && help[j].lowcost != INF)
            {
                if(min_index == -1)
                {
                    min_index = j;
                }
                else if(help[min_index].lowcost > help[j].lowcost)
                {
                    min_index = j;
                }
                else 
                {
                    continue;
                }
            }
        }

        help[min_index].lowcost = -2;
        sum += G[min_index][help[min_index].from];

        for(int k = 2; k <= n; k++)
        {
            if(help[k].lowcost == -2)
            {
                continue;
            }
            else 
            {
                if(G[min_index][k] < help[k].lowcost)//更新最短的路径
                {
                    help[k].lowcost = G[min_index][k];
                    help[k].from = min_index;
                }
            }
        }
    }
    return sum;
}

int main()
{
    read();
    cout << prim();
    return 0;
}