#pragma comment(linker, "/STACK:10240000000,10240000000")
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>
using namespace std;

vector<string> split(const string& str)
{
    stringstream input(str);
    string temp;
    vector<string> res;
    char pattern = ',';
    while (getline(input, temp, pattern))
    {
        if (temp != "")
        {
            res.push_back(temp);
        }
    }
    return res;
}

int StringToInt(string s)
{
    unsigned int i = 0, length = s.length();
    int num = -1;
    while (i < length)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            if (num == -1)
            {
                num = s[i] - '0';
            }
            else
            {

                num *= 10;
                num += s[i] - '0';
            }
        }
        i++;
    }
    return num;
}

//下面是要以站点为顶点，公交车为边，进行图的构建
typedef struct ArcNode 
{
    int adjvex;
    int road;                   //通过公交车road与adjvex号站点相连
    struct ArcNode* nextarc;    //指向下一条边
}ArcNode;

typedef struct VexNode 
{
                                //给每个站分配一个编号,用在Graph中数组的下标代替
    char name[50];              //站点名称
    ArcNode* firstArc;          //第一条边
}VexNode;

bool cmp(VexNode &a, VexNode &b) 
{
    if (strcmp(a.name, b.name) <= 0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

class Graph
{
private:
    VexNode stations[10005];     //储存站点信息的数组
    int vexnum, arcnum;         //点的数量，边的数量
    int* visit;

public:
    Graph();
    ~Graph();

    void AddArc(int u, int v, int road);
    //加边操作 从stations[u]到stations[v]有一条边，是通过road号车连接的
    
    void BFS(int u, int v);
    //利用BFS寻找从 u 号点到v号点的最短的路径(经过站点最少的)，直接进行路劲的打印

    ArcNode* GetFirstArc(int i);
    //获得某个站点的第一条边
    
    int GetVexnum();
    //获取所有的站点的数量
    
    int GetArcnum(int i);
    //获取某个站边的数量
    
    int FindStop(string s);
    
    string GetStopName(int i);

    bool IsAdj(int i, int j);

    VexNode* GetStations();

};

Graph::Graph()
{
    this->vexnum = 0;
    this->arcnum = 0;
    this->visit = NULL;
    for (int i = 0; i < 10000; i++) 
    {
        this->stations[i].firstArc = NULL;
        this->stations[i].name[0] ='0';
    }
    int u,v,road,cnt = 0;
    bool flag = false;

    string bus_number, stop_name_series;
    vector <string> res;
    
    fstream file("南京公交线路.txt", ios::in);
    while (!file.eof()) 
    {
        file >> bus_number >> stop_name_series;
        res = split(stop_name_series);
        for (vector<string>::iterator iter = res.begin(); iter != res.end(); iter++)
        {
            flag = false;
            for (int i = 0; i < this->vexnum; i++) 
            {
                if (strcmp(this->stations[i].name, iter->c_str()) == 0)
                {
                    flag = true;
                    break;
                }
            }
            if(!flag)
            {
                this->stations[vexnum].firstArc = NULL;
                //f << vexnum <<" "<< *iter << endl;
                strcpy_s(this->stations[vexnum].name, iter->c_str()); //如果是一个新的站，那么加进去
                this->vexnum++;
            }

        }
    }

    file.close();
    file.clear();

    file.open("南京公交线路.txt", ios::in);

    while (!file.eof())
    {
        file >> bus_number >> stop_name_series;
        
        road = StringToInt(bus_number);
        res = split(stop_name_series);
        cnt = 0;
        for (vector<string>::iterator iter = res.begin(); iter != res.end(); iter++)
        {
            cnt++;  //当前遍历车站的个数
            u = FindStop(*iter);
            if (cnt == 1) 
            {
                v = u;
                continue;
            }
            if (u != -1) 
            {
                AddArc(u, v, road); //加一条双向边
                v = u;
                this->arcnum++;
            }
        }
    }
    file.close();
    this->visit = new int[this->vexnum];
    for (int i = 0; i < this->vexnum; i++) 
    {
        this->visit[i] = 0;
    }
    /*for (int i = 0; i < 100; i++)
    {
        ArcNode* AD = this->stations[i].firstArc;
        while (AD != NULL) 
        {
            cout << AD->road << " " <<this->stations[i].name << " "<<GetStopName( AD->adjvex) << endl;
            AD = AD->nextarc;
        }
    }*/
}

Graph::~Graph()
{
    this->arcnum = 0;
    this->vexnum = 0;
    if (this->visit != NULL) 
    {
        free(this->visit);
        this->visit = NULL;
    }
}

void Graph::AddArc(int u, int v, int road) 
{
    ArcNode* AD = this->stations[u].firstArc;
    if (AD == NULL) 
    {
        this->stations[u].firstArc = new ArcNode;
        this->stations[u].firstArc->adjvex = v;
        this->stations[u].firstArc->road = road;
        this->stations[u].firstArc->nextarc = NULL;
    }
    else 
    {
        while (AD->nextarc != NULL) 
        {
            AD = AD->nextarc;
        }
        AD->nextarc = new ArcNode;
        AD = AD->nextarc;
        AD->adjvex = v;
        AD->road = road;
        AD->nextarc = NULL;
    }
    AD = this->stations[v].firstArc;

    if (AD == NULL)
    {
        this->stations[v].firstArc = new ArcNode;
        this->stations[v].firstArc->adjvex = u;
        this->stations[v].firstArc->road = road;
        this->stations[v].firstArc->nextarc = NULL;
    }
    else
    {
        while (AD->nextarc != NULL)
        {
            AD = AD->nextarc;
        }
        AD->nextarc = new ArcNode;
        AD = AD->nextarc;
        AD->adjvex = u;
        AD->road = road;
        AD->nextarc = NULL;
    }
    this->arcnum++;
}

ArcNode* Graph::GetFirstArc(int i) 
{
    return this->stations[i].firstArc;
}

int Graph::GetArcnum(int i) 
{
    ArcNode* AD = this->stations[i].firstArc;
    int num = 0;
    while (AD != NULL) 
    {
        num++;
        AD = AD->nextarc;
    }
    return num;
}

int Graph::GetVexnum()
{
    return this->vexnum;
}

bool Graph::IsAdj(int i, int j)
{
    //判断i和j两个站是否向邻接
    ArcNode* AS = this->stations[i].firstArc;
    ArcNode* AE = this->stations[j].firstArc;
    if (AS == NULL || AE == NULL)
    {
        return false;   //事实上，无向图的的一个点没有边，那么肯定不连接
    }
    else
    {
        while (AS != NULL)
        {
            if (AS->adjvex == j)
            {
                return true;
            }
            AS = AS->nextarc;
        }
        while (AE != NULL)
        {
            if (AE->adjvex == i)
            {
                return true;
            }
            AE = AE->nextarc;
        }
    }
    return false;
}

int Graph :: FindStop(string s)
{
    //查找某个站的编号
    for (int i = 0; i < this->vexnum; i++)
    {
        if (strcmp(stations[i].name, s.c_str()) == 0)
        {
            return i;
        }
    }
    return -1;
}

string Graph:: GetStopName(int i)
{ 
    return string(this->stations[i].name);
}

void Graph::BFS(int u, int v)
//从u向v进行广度优先搜索
{
    ArcNode* p = stations[u].firstArc;
    int temp = u;
    bool flag = false;

    queue<int> Q;

    visit[u] = 1;

    Q.push(u);

    while (!Q.empty())
    {
        //cout << "yes" << endl;
        if (flag)
        {
            break;
        }
        temp = Q.front();
        Q.pop();
        for (p = stations[temp].firstArc; p != NULL; p = p->nextarc)
        {
            if (this->visit[p->adjvex] == 0)
            {
                visit[p->adjvex] = visit[temp] + 1;
                //cout << p->adjvex << " " << v << endl;
                if (p->adjvex == v)
                {
                    flag = true;
                    break;
                }
                Q.push(p->adjvex);
            }

        }
    }
    cout << "----------------------------------------------------------" << endl;
    cout << "最短路线共经过 " << visit[p->adjvex] << "站" << endl;

    stack<int> trail;
    queue<int> bus;
    ArcNode* AD;
    trail.push(v);  //终点进栈
    int pre = v, k = 0;

    for (int i = visit[v] - 1; i > 1; i--)
    {
        for (int j = 0; j < this->vexnum; j++)
        {
            if (visit[j] == i && IsAdj(pre, j))
            {
                trail.push(j);
                pre = j;
                //cout << this->GetStopName(j) << endl;
                break;
            }
        }
    }

    cout << stations[u].name;
    pre = u;
    while (!trail.empty())
    {
        cout << " -> ";
        k = trail.top();
        trail.pop();
        AD = this->GetFirstArc(k);
        while (AD->adjvex != pre)
        {
            AD = AD->nextarc;
        }
        pre = k;
        if (bus.empty() || bus.front() != AD->road)
        {
            bus.push(AD->road);
            if (bus.size() != 1)
            {
                //cout << "(此处换乘 " << AD->road << "路 )";
            }
        }
        cout << GetStopName(k);
    }
    cout << endl;
    cout << "所需换乘的车次如下:" << endl;
    while (!bus.empty())
    {
        cout << bus.front() << "路 -> ";
        bus.pop();
    }
    cout << "end" << endl;
    return;
}

VexNode* Graph::GetStations()
{
    return this->stations;
}
typedef struct Arc 
{
    int adjvex;     //下一个公交车的编号
    char stop[50];  //中转站的名称
    Arc* nextArc;   //下一个条边的指针
}Arc;

typedef struct Vex 
{
                        //公交车编号,用Graph中的数组下标进行代替,注意下标要从1开始，因为没有0路公交车
    Arc* firstArc;
}Vex;

class BusGraph
{
private:
    Vex buss[1005];
    int vexnum, arcnum;
    int* visit;

public:
    BusGraph(Graph &G);
    ~BusGraph();
    void AddArc(int u, int v, string stop);

    void BFS(Graph &G,int u, int v);
    //利用BFS寻找从 u 号点到v号点的最短的路径(经过站点最少的)，直接进行相关的输出

    int GetVexnum();
    //获取所有的站点的数量

    int GetArcnum(int i);
    //获取某个公交车经过站的数量
    int FindBusNumber(int i);

    bool IsAdj(int i, int j);

    string GetTransfer(int u, int v);
};

BusGraph::BusGraph(Graph &G)

{
    this->arcnum = 0;
    this->vexnum = 0;
    this->visit = NULL;
    for (int i = 0; i <= 1000; i++)
    {
        this->buss[i].firstArc = NULL;
    }
    ArcNode* p, * q;
    Arc* AD;
    VexNode* stations = G.GetStations();
    bool f[1005];
    for (int j = 0; j <= 1000; j++)
    {
        f[j] = false;
    }
    for (int i = 0; i < G.GetVexnum(); i++) //遍历每个站 
    {   
        p = stations[i].firstArc;

        while (p != NULL) 
        {
            if (!f[p->road])        //数一下有多少路公交车
            {
                f[p->road] = true;
                this->vexnum++;
            }

            q = p->nextarc;
            while (q != NULL)
            {
                this->AddArc(p->road, q->road, string(stations[i].name)); 

                //注意我们保留了自环的边，这样防止只有一个车通过此站的站点不在任何一个车的边上
                
                this->arcnum++;
                q = q->nextarc;
            
            }
            p = p->nextarc;
        }
    }
    this->visit = new int[this->arcnum + 10];
}

BusGraph::~BusGraph()
{
}

void BusGraph::BFS(Graph &G,int u, int v)
//为了方便，这里的u和v我们也用站点的编号，这就需要将站点的车的信息取出来
{
    queue<int> Q; //用来搜索的队列，放的是公交车编号
    VexNode* stations = G.GetStations();
    ArcNode* AD = stations[u].firstArc; //找到起点的第一条边
    Arc* AC = NULL;
    int k = 0;
    bool flag = false;
    for (int i = 1; i < this->vexnum; i++)
    {
        visit[i] = 0;
    }
    while (AD != NULL)      //把起点站的所有可乘车放进队列中
    {
        Q.push(AD->road);
        this->visit[AD->road] = 1; //上车就算了一次，与别的线路区分开
        AD = AD->nextarc;
    }
    while (!Q.empty())
    {
        if (flag)
        {
            break;
        }
        k = Q.front();  //取出一条公交路线
        Q.pop();
        AC = this->buss[k].firstArc;   //遍历这条公交路线的所有车站
        while (AC != NULL)
        {
            if (visit[AC->adjvex] == 0) //可以抵达一个新的公交路线，那么搜索深度加一
            {
                visit[AC->adjvex] = visit[k] + 1;
                Q.push(AC->adjvex);
            }
            if (strcmp(AC->stop, stations[v].name) == 0)
            {
                flag = true;
                break;
            }
            AC = AC->nextArc;
        }
    }

    //搜索到最少换乘的路线之后，现在进行输出
    stack<int> BU;
    int pre = k;    //k为最后乘坐的一个公交车
    BU.push(k);

    /*cout <<"visit[k] = " <<visit[k] << endl;*/
    for (int deep = visit[k] - 1; deep > 0; deep--) 
    {

        for (int j = 1; j <= this->vexnum; j++)
        {

            if (deep == visit[j] && this->IsAdj(j, pre))
            {
                BU.push(j);//找到了邻接点(线路)
                break;
            }
        }
    }
    queue<int> sim;
    sim.push(BU.top());
    cout << "---------------------------------------------------------" << endl;
    cout << "最短路线共经过 "<<visit[k] - 1<<" 次换乘" << endl;
    cout << "换乘次数最少的路线如下 : " << endl;
    cout << "从 " << G.GetStopName(u) << " 乘坐 " ;
    pre = BU.top();
    cout << pre << " 路";
    BU.pop();
    while (!BU.empty())
    {
        k = BU.top();
        cout << " -> 在 ";
        cout <<  GetTransfer(pre, k)<< " 站换乘 ";
        cout <<k<< " 路";
        sim.push(k);
        pre = k;
        BU.pop();
    }
    cout << " -> 最终到达 " << G.GetStopName(v) << endl;
    cout << endl;
    cout << "所需乘坐的公交线路如下 : " << endl;
    cout << sim.front()<<" 路";
    sim.pop();
    while (!sim.empty())
    {
        cout << " -> ";
        cout <<" "<< sim.front()<<" 路";
        sim.pop();
    }
    cout << endl;
}

void BusGraph::AddArc(int u, int v, string stop)
//u和v是转化后的下标
{
    Arc* AD = this->buss[u].firstArc;
    Arc* p = this->buss[u].firstArc;

    while (p != NULL)    //为了减少一些运算量，我们去除了重边
    {
        if (p->adjvex == v) 
        {
            if (strcmp(p->stop, stop.c_str()) == 0) 
            {
                return;     
            }
        }
        p = p->nextArc;
    }
   
    if (AD == NULL) 
    {
        this->buss[u].firstArc = new Arc;
        this->buss[u].firstArc->adjvex = v;
        this->buss[u].firstArc->nextArc = NULL;
        strcpy_s(this->buss[u].firstArc->stop, stop.c_str());
    }
    else 
    {
        while (AD->nextArc != NULL) 
        {
            AD = AD->nextArc;
        }
        AD->nextArc = new Arc;
        AD = AD->nextArc;
        AD->adjvex = v;
        AD->nextArc = NULL;
        strcpy_s(AD->stop, stop.c_str());
    }

    AD = this->buss[v].firstArc;
    
    if (AD == NULL)
    {
        this->buss[v].firstArc = new Arc;
        this->buss[v].firstArc->adjvex = u;
        this->buss[v].firstArc->nextArc = NULL;
        strcpy_s(this->buss[v].firstArc->stop, stop.c_str());
    }
    else
    {
        while (AD->nextArc != NULL)
        {
            AD = AD->nextArc;
        }
        AD->nextArc = new Arc;
        AD = AD->nextArc;
        AD->adjvex = u;
        AD->nextArc = NULL;
        strcpy_s(AD->stop, stop.c_str());
    }
    this->arcnum++;
    return;
}

int BusGraph::GetVexnum()
{
    return this->vexnum;
}

int BusGraph::GetArcnum(int i) 
{
    return this->arcnum;
}

int BusGraph::FindBusNumber(int i)
{
    if (i <= this->vexnum) 
    {
        return i;
    }
    else 
    {
        return -1;
    }
}

bool BusGraph::IsAdj(int i, int j) 
{
    //判断两个公交车有没有相邻的边（是否经过同一个站点）
    Arc* AD = this->buss[i].firstArc;
    Arc* AS = this->buss[j].firstArc;
    if (AD == NULL || AS == NULL) 
    {
        return false;   //如果有的公交车没有站点，是访问越界或者建图错误
    }
    else 
    {
        while (AD != NULL) 
        {
            if (AD->adjvex == j) 
            {
                return true;
            }
            AD = AD->nextArc;
        }
        while (AS != NULL)
        {
            if (AS->adjvex == i)
            {
                return true;
            }
            AS = AS->nextArc;
        }
    }
    return false;
}

string BusGraph::GetTransfer(int u, int v) 
{
    Arc* AD = this->buss[u].firstArc;
    if (!this->IsAdj(u , v))
    {
        return "-1";  //如果不相邻的两个线路，返回空字符串
    }
    else 
    {
        while (AD != NULL)
        {
            if (AD->adjvex == v)
            {
                string s(AD->stop);    //找到连接的站点，把名称返回回去
                return s;
            }
            AD = AD->nextArc;
        }
    }
}

void Conseal() 
{
    Graph* p;
    p = new Graph;
    BusGraph* Bp;
    Bp = new BusGraph(*p);
    string s, e, res = "yes";
    int u=-1, v=-1;
    while (res == "yes" || res == "y" || res == "Y" || res == "1")
    {
        system("cls");
        cout << "----------------------------------------------------------" << endl;
        cout << "欢 迎 使 用 公 交 路 线 提 示 系 统" << endl;
        cout << "请输入起始站 : ";
        cin >> s;

        u = p->FindStop(s);
        while (u == -1)
        {
            cout << "输入的起始站 " << s << " 为非法输入，请重新输入 : ";
            cin >> s;
            u = p->FindStop(s);
        }

        cout << endl << "请输入终点站 : ";
        cin >> e;
        v = p->FindStop(e);
        while (v == -1)
        {
            cout << "输入的终点站 " << e << " 为非法输入，请重新输入 : ";
            cin >> e;
            v = p->FindStop(e);
        }
        cout << "----------------------------------------------------------" << endl;
        if (u == v)
        {
            cout << "起始站和终点站为同一地点，无需乘车" << endl;
        }
        else
        {
            p->BFS(u, v);
            Bp->BFS(*p, u, v);
        }
        cout << "是否需要继续查询？(yes or no)" << endl;
        cin >> res;
    }
    return ;
}
//控制台函数

int main()
{
    Conseal();
    return 0;
}


