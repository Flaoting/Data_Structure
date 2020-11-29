#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
int M = 10, N = 10; 
int Matrix[100][100];

int main()
{
    
 
    fstream file ("2.txt",ios::in);
    file >> M >> N;
    for (int i = 1; i <= M; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            file >> Matrix[i][j];
        }
    }
    int row_min[M+5];

    for (int i = 1; i <= M; i++) 
    {
        row_min[i] = 1;
        for (int j = 1; j <= N; j++)
        {
            if(Matrix[i][row_min[i]] > Matrix[i][j])
            {
                row_min[i] = j;
            }
        }
    }

    int ans_i = -1, ans_j = -1;
    bool ans = false;

    for (int i = 1; i <= M; i++)
    {
        int j = 0;
        for (j = 1; j <= M; j++)
        {
            if (j == i)
            {
                continue;    
            }
            if(Matrix[i][row_min[i]] <= Matrix[j][row_min[i]])
            {
                break;
            }
        }
        if(j == N + 1) //如果某一列循环到了最后，那么找到了鞍点
        {
            ans = true;
            ans_i = i;
            ans_j = j-1;
            break;      //经过证明，鞍点只有一个,那么找到一个就可以停止了
        }
    }
    cout << ans_i<< " " << ans_j<<endl;
    return 0;
}