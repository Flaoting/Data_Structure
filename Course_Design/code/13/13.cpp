#include <iostream>
#include <fstream>
using namespace std;
int n,m;
int G[105][105]; //默认不超过100行 100 列
bool flag[105][105];
bool help[105][105];

void read()
{
    fstream file("13.txt",ios::in);
    file >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            file >> G[i][j];
        }
    }
    file.close();
}

void show()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cout << G[i][j] << " ";
        }
        cout <<endl;
    }
}

int con = 0, p = 1;
bool row( ) // 行和列
{
    for(int i = 1; i <= n; i++)
    {
        p = 1;
        con = 0;
        do
        {
            con = 1;
            while(p + 1 <= m && G[i][p] == G[i][p + 1])
            {
                con ++;
                p++;
            }
            
            if(con >= 3)
            {
                while(con--)
                {
                    flag[i][p-con] = true;
                    //cout << "p = "<<p<<" con = "<<con << endl;
                }
            }
            else
            {
                con = 1;
            }
        p++;

        }while(p <= m);
    }
}

bool col()
{
    for(int i = 1; i <= m; i++)
    {
        p = 1; 
        con = 1;
        do
        {
            while(p + 1 <= n && G[p][i] == G[p+1][i])
            {
                con ++;
                p++;
            }
            if(con >= 3)
            {
                while(con--)
                {
                    flag[p-con][i] = true;
                }
            }
            else
            {
                con = 1;
            }
            p++;
        }while(p <= m);
    }
}
int delete_f()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(flag[i][j])
            {
                G[i][j] = 0;
            }
        }
    }
}
int main()
{
    read();
    row();
    col();
    delete_f();
    show();
    return 0;
}