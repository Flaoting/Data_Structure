#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
int T;
int cheese[5][5];


void read()
{
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            cin >> cheese[i][j];
        }
    }
}
//读入棋盘

int space()
{
    int sum = 0;
    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++)
        {
            if(cheese[i][j] == 0)
            {
                sum ++;
            } 
        }
    }
    return sum;
}
//计算空格数

int simple()
{
    int sum = 0;
    for(int i = 1; i <= 3; i++)
    {
        if(cheese[i][1] == 0 || cheese[i][2] == 0 || cheese[i][3] == 0 )
        {
            continue;
        }
        else
        {
            sum = cheese[i][1] + cheese[i][2] + cheese[i][3];
        }

        if(sum == 6)
        {
            return 2; //Bob 
        }
        else if(sum == 3)
        {
            return 1; //Alice
        }
        else
        {
            sum = 0;
        }
    }

    for(int i = 1; i <= 3; i++)
    {

        if(cheese[1][i] == 0 || cheese[2][i] == 0 || cheese[3][i] == 0 )
        {
            continue;
        }
        else
        {
            sum = cheese[1][i] + cheese[2][i] + cheese[3][i];
        }

        if(sum == 6)
        {
            return 2; //Bob 
        }
        else if(sum == 3)
        {
            return 1; //Alice
        }
        else
        {
            sum = 0;
        }
    }

    if(cheese[1][1] != 0 && cheese[2][2] != 0 && cheese[3][3] !=0)
    {
        sum = cheese[1][1] + cheese[2][2] + cheese[3][3];
        if(sum == 6)
        {
            return 2; //Bob 
        }
        else if(sum == 3)
        {
            return 1; //Alice
        }
        else
        {
            sum = 0;
        }
    }

    if(cheese[1][3] != 0 && cheese[2][2] != 0 && cheese[3][1] !=0)
    {
        sum = cheese[1][3] + cheese[2][2] + cheese[3][1];
        if(sum == 6)
        {
            return 2; //Bob 
        }
        else if(sum == 3)
        {
            return 1; //Alice
        }
        else
        {
            sum = 0;
        }
    }
    return 0; // 当前无人胜出
}
//判断当前的局面有没有人赢了

int caculate()
{
    int si = simple();
    int sn = space();
    if(si == 0)
    {
        return 0;
    }
    else if(si == 1)
    {
        return sn+1;
    }
    else if(si == 2)
    {
        return (sn + 1)*(-1);
    }
    else
    {
        return 0;
    }
}
//计算棋局分数

int space_num = 0;
int win_num = 0;
int score = 0;

int dfs(int id)  //当前到谁走，1为AIice ，2 为Bob
{
    if(space() == 0)
    {
        return 0;
    }
    int max_score = -10;
    int min_score = 10;

    for(int i = 1; i <= 3; i++)
    {
        for(int j = 1; j <= 3; j++ )
        {
            if(cheese[i][j] == 0)
            {
                cheese[i][j] = id;

                if(simple()) //有人赢了
                {
                    score = caculate();
                    cheese[i][j] = 0;
                    return score > 0 ? max(max_score,score) : min(min_score,score);
                }

                if(id == 1)
                {
                    max_score = max(max_score,dfs(2));
                }
                else
                {
                    min_score = min(min_score,dfs(1));
                }
                cheese[i][j] = 0;//回溯
            }

        }
    }
    return id == 1 ? max_score : min_score;
}


int main()
{
    cin >> T;
    for(int i = 1; i <= T; i++)
    {
        read();
        space_num = space();
        win_num = simple();

        if(win_num == 1)
        {
            cout << space_num + 1 << endl;
        }   
        else if(win_num == 2)
        {
            space_num ++;
            space_num*=-1;
            cout << space_num << endl;
        }
        else        //当前状态不满足的时候
        {
            cout << dfs(1) << endl;
        }
    }
    return 0;
}

