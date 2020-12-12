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
            cout << map[i][j]<< " ";
        }
        cout << endl;
    }
    return ;
}
void copy(int x, int y)
{
    cout << "x = " << x << " y = "<<y <<endl;
    for (int i = 1 ;i <= 4;i ++)
    {
        for (int j = 1; j <= 4; j++)
        {
            if(map[x+i-1][j+y-1] == 0 && object[i][j] == 1)
            {
                map[x+i-1][j+y-1] = 1;
            }
        }
    }
    return;
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

    for (int i = 1; i <= 4; i++)
    {
        for(int j = 1; j <= 4; j ++)
        {
            file >> object[i][j];
        }
    }
    file >> position ;
}
int main()
{
    read();
    for (int i = 0; i <= 16; i++)
    {
        max_col[i] = 16;
    }

    for (int i = 0; i <= 8; i++)
    {
        min_col[i] = -1;
    }
    bool flag = false;
    for (int j = 1; j <= 10; j++)
    {
        flag = false;
        for (int i = 1; i <= 15; i++)
        {
            if(map[i][j] != 0)
            {
                max_col[j] = i;
                flag = true;
                //cout << i << " ";
                break;
            }
        }
        if(!flag)
        {
            max_col[j] = 16;
        }
    }
    cout <<endl;

    for (int j = 1; j <= 4; j++)
    {
        flag = false;
        for (int i = 4; i >= 1; i--)
        {
            if(object[i][j] != 0)
            {
                min_col[j] = i;
                //cout << i << " ";
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            min_col[j] = -1;
        }
    }
    cout <<endl;

    int min_index = 0;//列数
    int min_size = 9999;
    int min_arr[15];

    for (int j = 1; j<=4; j++)
    {
        min_arr[j] = max_col[j + position - 1] - min_col[j];

        if(min_size > min_arr[j])
        {
            min_index = j;
            min_size = min_arr[j];
        }

    }
    cout << min_index <<endl;
    int min_index_row = min_col[min_index]; //行数
    cout <<min_index_row <<endl;
    cout << max_col[position + min_index - 1] << endl ;
    //传入左上角的点
    copy(max_col[position + min_index - 1] - 1, position);
    print();
    return 0;
}