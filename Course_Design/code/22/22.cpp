/*22、【3】最小生成树 (选做) （图）
[问题描述]
利用普利姆算法和克鲁斯卡尔算法实现最小生成树问题。
[基本要求]
（1）自行建立图的数据文件，第一行是顶点个数，然后依次是顶点名，接下来是边，用float表示边的权值；
（2）以邻接表或者邻接矩阵表示图皆可；
（3）分别利用Prim和Kruskal算法实现最小生成树；
（4）输出最小生成树的权值之和，及所用的边。
*/

#include <queue>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#define ElemType int
#define MAX_SIZE 1005
#define INF 22222222

typedef struct edge 
{	
	int u, v;
	float w;
	bool operator < (const edge &a)const 
	{
		return w > a.w;
	}
}edge;	//kruskal用

typedef struct Vex
{
	//ElemType data;
	int NO;
}Vex;
Vex node[MAX_SIZE + 20];

int n, m;	//顶点个数和边的个数

priority_queue <edge> Kq;
int fa[MAX_SIZE + 10];

void initFa()
{
	for (int i = 0; i <= MAX_SIZE; i++)
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

void showEdge(edge e)
{
	cout << "u = " << e.u << "  v = " << e.v << " w = " << e.w << endl;
	return;
}

void AddEdge(int u, int v, float w)
{
	
	edge temp;
	temp.u = u;
	temp.v = v;
	temp.w = w;
	Kq.push(temp);	//把边放进优先队列里
	return;
}

void AddArc(int u, int v, float w);

void read() 
{
	FILE* stream;
	int u, v;
	float w;
	freopen_s(&stream, "22.txt", "r", stdin);
	cin >> n;

	for (int i = 1; i <= n; i++) 
	{
		cin >> node[i].NO;
	}
	cin >> m;

	for (int i = 1; i <= m; i++) 
	{
		cin >> u >> v >> w;
		AddEdge(u, v, w);
		AddArc(u, v, w);
		AddArc(v, u, w);
	}
}

void kruskal() 
{
	edge now;
	float ans = 0;
	int cnt = 0;

	cout << "-----------------------------------------------------------" << endl;
	cout << "Now is Kruskal algorithm " << endl;
	while (!Kq.empty() && cnt < n-1) 
	{
		now = Kq.top();
		Kq.pop();
		if (findFa(now.u) == findFa(now.v))
		{
			continue;
		}
		else
		{
			fa[findFa(now.v)] = fa[findFa(now.u)];
			showEdge(now);
			ans += now.w;
			cnt++;
		}
	}

	cout << "Prim answer is " << ans << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << endl;
}


typedef struct Arc
{
	int adjvex;		//邻接点
	float weight;		//权值
}Arc;	//prim用

vector <Arc> vex[MAX_SIZE + 10];	//存图，每个vector中存着对应标号的边，原理类似于邻接表

void AddArc(int u, int v, float w)
{
	Arc temp;
	temp.adjvex = v;
	temp.weight = w;
	vex[u].push_back(temp);
}

void prim() 
{
	bool isChoosed[MAX_SIZE + 10];
	float dis[MAX_SIZE + 10], min = 0,ans = 0;

	int pre[MAX_SIZE + 10], cnt = 0, k = 1;
	
	for (int i = 0; i <= MAX_SIZE; i++)
	{
		dis[i] = INF;
		isChoosed[i] = false;
	}

	dis[1] = 0;
	
	isChoosed[1] = true;
	cnt++;
	
	for (vector<Arc>::iterator iter = vex[1].begin(); iter != vex[1].end(); iter++)
	{
		dis[iter->adjvex] = iter->weight;
		pre[iter->adjvex] = 1;
	}
	cout << "-----------------------------------------------------------" << endl;
	cout << "Now is Prim algorithm " << endl;
	while (cnt < n)
	{
		k = 1;

		while (isChoosed[k]) 
		{
			k++;
		}

		min = dis[k];	//第k个点的距离是多少
		
		for (int i = 2; i <= n; i++) 
		{
			if (isChoosed[i])
			{
				continue;
			}
			else 
			{
				if (min > dis[i]) 
				{
					min = dis[i];
					k = i;
				}
			}
		}	//min是当前距离最小的下标
		//cout << k <<"    "<< dis[k] << endl;
		isChoosed[k] = true;
		for (vector<Arc>::iterator iter = vex[k].begin(); iter != vex[k].end(); iter++)
		{
			if (!isChoosed[iter->adjvex] && dis[iter->adjvex] > iter->weight)
			{
				dis[iter->adjvex] = iter->weight;
				pre[iter->adjvex] = k;
			}
		}
		ans += dis[k];
		cout << "u = " << pre[k] << " v = " << k << " w = " << dis[k] << endl;
		dis[k] = 0;
		cnt++;
	}
	cout << "Prim answer is " << ans << endl;
	cout << "-----------------------------------------------------------" << endl;
	return;
}


int main() 
{
	read();
	initFa();
	kruskal();
	prim();

}

