#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

#define ElemType int
#define INFINITY INT_MAX        //定义正无穷
#define MAX_V 20    //最大定点数目
#define GraphKind int       //声明图的标志 1无向图 2有向图 3有向网 4无向网


typedef struct  
{
    
    int code;       //结点编号0~G.vernum
    ElemType info;  //结点其他信息，这里是点权

}VertexType;

typedef struct
{
    int arcs[MAX_V][MAX_V];     //邻接矩阵
    int vexnum, arcnum;         //顶点个数和边的个数
    VertexType vexs[MAX_V];     //存放定点信息
    GraphKind type;
}MGraph;        //图的邻接矩阵类型

bool CreateGraph(MGraph &G, string FileName)
{
    fstream file(FileName.c_str(),ios::in);
    if(!file)
    {
        cout << "Floating TIP   File " << FileName << " can't be opened !"<<endl;
        return false;
    }

    file >> G.type;     //输入图的类型
    file >> G.vexnum >> G.arcnum ;

    for(int i = 0; i<G.vexnum; i++)
    {
        G.vexs[i].code = i;
        file >> G.vexs[i].info;
    }

    for(int i = 0; i < G.vexnum; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = 0;
        }
    }

    int x = 0, y = 0;
    for(int i = 0; i < G.arcnum; i++)
    {
        file >> x >> y;
        G.arcs[x][y] = 1;
        G.arcs[y][x] = 1;
    }
    return true;
}
//建立无向图

void DestroyGraph(MGraph &G)
{
    for(int i = 0; i < G.vexnum; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = 0;
        }
    }

    for(int i = 0; i<G.vexnum; i++)
    {
        G.vexs[i].code = 0;
        G.vexs[i].info = 0;
    }

    G.arcnum = 0;
    G.vexnum = 0;
    G.type = -1;
    return;
}
//销毁无向图

VertexType GetVex(MGraph G, int v)      //v是编号，返回元素值
{
    VertexType e;
    if(v < 0 || v >= G.vexnum)
    {
        e.code = -1;
        e.info = -1;
        return e;
    }
    else 
    {    
        e = G.vexs[v];
        return e;
    }
}
//返回下标为v的元素值

int FirstAdjVex(MGraph G, int v)
{
    if(v < 0 || v >= G.vexnum)
    {
        return -1;
    }

    bool flag = false;
    
    for(int j = 0; j < G.vexnum; j++)
    {
        if(G.arcs[v][j] == 1)
        {
            flag = true;
            return j;
        }
    }
    
    if(!flag)
    {
        return -1;      //找不到邻接点
    }

}

int NextAdjVex(MGraph G, int v, int w)
{
    if(v < 0 || v >= G.vexnum)
    {
        return -1;
    }
    
    bool flag = false;
    for(int j = w + 1; j < G.vexnum; j++)
    {
        if(G.arcs[v][j] == 1)
        {
            flag = true;
            return j;
        }
    }
    if(!flag)
    {
        return -1;
    }
}

void VisitVertex(VertexType Ver)
{
    cout << "Code : "<<Ver.code << "  Info : " << Ver.info << "  "<<endl;
    return;
}
//访问的函数

void DFSTraverse(MGraph G, int v) //v记录当前遍历到的结点
{
    bool flag[G.vexnum];
    stack <int> S;
    S.push(v);  //从v开始进行遍历
    int now;
    while(!S.empty())
    {
        now = S.top();
        VisitVertex(G.vexs[now]);
        flag[now] = true;
        S.pop();
        for(int j = 0; j < G.vexnum; j++)
        {
            if(G.arcs[now][j] == 1 && !flag[j])  //找到一个连接的点，并且没有访问过
            {
                S.push(j);
            }
        }
    }
    return ;
}
//进行深度优先遍历

void BFSTraverse(MGraph G, int v)
{
    bool flag[G.vexnum];
    queue <int> Q;
    int now;

    VisitVertex(G.vexs[v]);
    flag[v] = true;
    Q.push(v);

    while(!Q.empty())
    {
        now = Q.front();
        Q.pop();
        for(int j = 0; j <G.vexnum; j++)
        {
            if(G.arcs[now][j] == 1 && !flag[j])
            {
                VisitVertex(G.vexs[j]);
                flag[j] = true;
                Q.push(j);
            }
        }
    }
    return;
}
//广度优先遍历

void InsertVex(MGraph &G, VertexType ver)
{
    if(G.vexnum == MAX_V)
    {
        cout << "Memory is overflowed, vertex can't insert !"<<endl;
    }
    ver.code = G.vexnum;
    G.vexs[G.vexnum] = ver; //储存顶点信息
    G.vexnum++;
    for(int i = 0; i < G.vexnum; i++)
    {
        G.arcs[ver.code][i] = 0;
        G.arcs[i][ver.code] = 0;
    }
    return;
}
//插入一个顶点

void InsertArc(MGraph &G, int v, int w) 
{
    if(v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum)
    { 
        cout << "can't add edge"<<endl;
        return ;
    }
    G.arcs[v][w] = 1;
    G.arcs[w][v] = 1;
    G.arcnum ++;
    return;
}
//插入一条边

void DeleteVex(MGraph &G, int v)
{
    if(v < 0 || v >= G.vexnum)
    { 
        cout << v <<" vertex is not exist !"<<endl;
        return ;
    }

    for(int i = 0; i < G.vexnum; i++)
    {
        if(G.arcs[i][v] == 1 || G.arcs[v][i] == 1)
        {
            G.arcnum--;
        }
        G.arcs[v][i] = 0;
        G.arcs[i][v] = 0;
    }
    //直接全扫一遍
    for(int i = v; i < G.vexnum - 1; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = G.arcs[i+1][j];
        }   
    }

    for(int i = 0; i < G.vexnum - 1; i++)
    {
        for(int j = v; j < G.vexnum - 1; j++)
        {
            G.arcs[i][j] = G.arcs[i][j+1];
        }
    }

    for(int i = v; i < G.vexnum - 1; i++)
    {
        G.vexs[i] = G.vexs[i+1];
        G.vexs[i].code--;
    }
    //对点进行移位
    G.vexnum--;
    return;
}

void DeleteArc(MGraph &G, int v, int w)
{
    if(v < 0 || v >= G.vexnum || w < 0 || w >= G.vexnum)
    { 
        cout << "Can't delete edge"<<endl;
        return ;
    }
    if(G.arcs[v][w] == 1 || G.arcs[w][v] == 1)
    {
        G.arcs[v][w] = 0;
        G.arcs[w][v] = 0;
        cout << "Floating TIP   Delete the arc betewwn " << v << " and "<< w << " successfully ! "<<endl;
    }
    else
    {
        cout << "Floating TIP   The arc between "<< v << " and "<< w<< " is now exist."<<endl;
    }
    return;
}

void DisplayMGraph(MGraph G)
{
    if(G.vexnum == 0 && G.vexnum ==0)
    {
        cout << "NULL Graph"<<endl;
    }
    for(int i = 0; i < G.vexnum; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            cout << G.arcs[i][j]<< " ";
        }
        cout << endl;
    }
}

int main()
{
    string f = "1.txt";
    MGraph G;
    VertexType V;
    V.code =100;
    V.info = 99;
    CreateGraph(G,f);
    DisplayMGraph(G);
    cout << endl;
    DFSTraverse(G,1);
    cout << endl;
    DisplayMGraph(G);
    cout << endl;
    BFSTraverse(G,1);
    //DestroyGraph(G);
    //VisitVertex(V);
    //V = GetVex(G,1);
    //VisitVertex(V);
    //DisplayMGraph(G);
    
    // DisplayMGraph(G);
    // cout << FirstAdjVex(G,2)<<endl;;
    // cout << NextAdjVex(G,2,1);
    DeleteVex(G,1);
    DisplayMGraph(G);
    cout <<endl;
    DeleteVex(G,2);
    DisplayMGraph(G);
    cout <<endl;
    cout <<endl;
    DeleteVex(G,2);
    DisplayMGraph(G);
    cout <<endl;
    return 0;
}
