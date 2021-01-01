#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <concurrent_priority_queue.h>
using namespace std;
#define MAX_SIZE 1005 //最大点数
#define MAX_EDGE 2005
#define INF 22222222
typedef struct edge 
{
	int u, v, w;
	bool operator < (const edge& a)const
	{
		return w > a.w;
	}
}edge;		//双向边储存，为了排序

priority_queue <edge> e;	//存边的堆

int n, m;
int fa[MAX_SIZE + 5];	//并查集

void InitFa()
{
	for (int i = 1; i <= n; i++) 
	{
		fa[i] = i;
	}
	return;
}

int findFa(int i)
{
	if (fa[i] != i)
	{
		return findFa(fa[i]);
	}
	else 
	{
		return i;
	}
}

void AddArc(int u, int v, int w)
{
	edge temp;
	temp.u = u;
	temp.v = v;
	temp.w = w;
	e.push(temp);
	return;
}

void show(edge c)
{
	cout << c.u << " " << c.v << " " << c.w << endl;
}

void read() 
{
	FILE * s;
	freopen_s(&s, "5.txt", "r", stdin);
	cin >> n >> m;
	int u, v, w;
	for (int i = 1; i <= m; i++) 
	{
		cin >> u >> v >> w;
		AddArc(u, v, w);
	}
}

int kruskal() 
{
	if (n <= 1)
	{
		return 0;	//特判，一个节点或者零个节点
	}
	edge now;
	int min = INF;
	bool flag = false;
	while (!e.empty()) 
	{
		//cout << "fa[1] = " << findFa(1) << "fa[n] = " << findFa(n) << endl;
		if (findFa(1) == findFa(n)) 
		{
			flag = true;
			break;
		}
		now = e.top();
		e.pop();
		if (findFa(now.u) == findFa(now.v))	//要在同一个连通块的话，就不可以加这条边
		{
			show(now);
			continue;		
		}
		else					
		{
			min = now.w;
			fa[findFa(now.v)] = fa[findFa(now.u)];
			//加入这条边

			//if (findFa(now.u) == now.u && findFa(now.v) == now.v)
			//{
			//	fa[now.v] = now.u;	//两个都是单独的点，或者都是根
			//}
			//else if (findFa(now.u) == now.u && findFa(now.v) != now.v)
			//{
			//	fa[now.u] = now.v;	//一个并入另一个连通块
			//}
			//else if (findFa(now.u) != now.u && findFa(now.v) == now.v)
			//{
			//	fa[now.v] = now.u;	//一个并入另一个连通块
			//}
			//else			//两个连通块合并 
			//{
			//	fa[findFa(now.v)] = fa[findFa(now.u)];
			//}
		}
	}
	if (flag)
	{
		cout << min << endl;
	}
	else 
	{
		cout << "error" << endl;
	}
}

int main()
{
	read();
	InitFa();
	kruskal();
	return 0;
}


