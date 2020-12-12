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
int read()
{

    for (int i = 1; i <= 15; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            cin >> map[i][j];
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
            cin >> object[i][j];
        }
    }
    cin >> position ;
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
        for(int i = 14; i >= 1; i--)
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
    read();
    start();
    while(judge())
    {
        drop();
    }
    print();
    return 0;
}