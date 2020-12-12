#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
int map[20][20];
int object[10][10];
int position = 0;
int max_col[20];
int min_col[10];

void print()
{
    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            if(map[i][j] != 0)
            {
                cout << "1";
            }
            else 
            {
                cout << "0";
            }
            cout <<" ";
        }
        cout << endl;
    }
    return ;
}
void test_print()
{
     for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            cout <<map[i][j]<< " ";
        }
        cout << endl;
    }
    return ;
}
int read()
{
    fstream file("5.txt",ios::in);
    if(!file)
    {
        cout << "file can't be opened !"<<endl;
        exit(0);
    }

    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            file >> map[i][j];
        }
    }
    for (int j = 1; j <= 10; j++)
    {
        map[16][j] = 1;
    }

    for (int i = 1; i <= 4; i++)
    {
        for(int j = 1; j <= 4; j ++)
        {
            file >> object[i][j];
        }
    }
    file >> position ;
}

void start()
{
    for(int i = 1; i <= 4; i++)
    {
        for(int j = 1; j <= 4; j++)
        {
            if(object[i][j] != 0)
            {
                map[i][position+j-1] = 2;
            }
            
        }
    }
    return ;
}

void drop( )
{  
    for (int j = 0; j < 4; j++)
    {
        for(int i = 15; i >= 1; i--)
        {
            if(map[i][j+position] == 2)
            {
                map[i+1][j+position] = map[i][j+position];
                map[i][j+position] = map[i-1][j+position];
            }
        }
    }
    return;
}

int cnt = 0;

void dfs(int x, int y)
{
    if(map[x][y] == 0) 
    {
        cout<<"yes"<<endl;
        return;
    }
    else
    {
        cnt++;
        map[x][y] = 0;
        if(x + 1 < 16 && map[x+1][y] != 0)
        {
            dfs(x+1,y);
        }
        if(x - 1 > 0 && map[x-1][y] != 0)
        {
            dfs(x-1,y);
        }
        if(y + 1 < 11 && map[x][y+1] != 0)
        {
            dfs(x,y+1);
        }
        if(y - 1 > 0 && map[x][y-1] != 0)
        {
            dfs(x,y-1);
        }
        map[x][y] = 2;
    }
}
void FindFirst(int &x, int &y)
{
    for(int i = 1; i <= 15; i++)
    {
        for(int j = 1; j <= 10; j++)
        {
            if(map[i][j] == 2)
            {
                x = i;
                y = j;
                return ;
            }
        }
    }
    return;
}
bool judge()
{
    int sum = 0;
    int cnt_1 = 0;
    bool flag = false;
    for (int j = 0; j < 4; j++)
    {
        flag = false;
        for(int i = 15; i >= 1; i--)
        {
            if(map[i][j+position] == 2)
            {
                flag = true;
                if(map[i+1][j+position] == 0)
                {
                    cnt_1++;
                }
            }
            
        }
        if(flag)
        {
            sum ++;
        }
    }
    if(sum == cnt_1)
    {
        return true;
    }
    else 
    {
        return false;
    }
}
int main()
{
    int x = 1, y =1;
    read();
    start();
    do
    {
        if(cnt == 4)
        {
            drop();
        }
        cnt = 0;
        FindFirst(x,y);
        cout << "x = "<<x<<"  y = "<<y << endl;
        dfs(x,y);
    }while(cnt == 4);
    while(judge())
    {
        drop();
    }
    cout << endl;
    print();
    return 0;
}