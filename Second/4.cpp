#include <iostream>
#include <fstream>
using namespace std;
int N=0;
int T=0,E=0,D=0;
int t[1005];
bool e[1005];
int m[1005][1005];
int main()
{
    ifstream file("4.txt",ios::in);
    if(!file)
    {
        cout << "File can't be opened!"<<endl;
        exit(0);
    }
    file>>N;
    //cin>>N;
    int mi=0,temp=0;
    for (int i=1; i<=N; i++)
    {
        //cin>>mi;
        file>>mi;
        for(int j=1; j<=mi; j++)
        {
            file>>m[i][j];
            //cin>>m[i][j];
        }

        for(int j=mi; j>=1; j--)
        {
            if (m[i][j]<=0)
            {
                t[i]+=m[i][j];
            }
            else
            {
                t[i]+=m[i][j];
                T+=t[i];
                break;
            }
        }
        int now = 0, sub = 0;
        for(int j=1; j<=mi; j++)
        {
            if(m[i][j]>0)
            {
                if(now == 0)
                {
                    now = m[i][j];
                    continue;
                }
                else
                {
                    if (m[i][j]!=now+sub)
                    {
                        E++;
                        e[i]=1;
                        // cout <<"m[i][j] = " << m[i][j]<<endl;
                        // cout << "i = "<<i<<endl;
                        break;
                    }
                    now = m[i][j];
                    sub = 0;
                }
               
            }
            else if(m[i][j]<=0)
            {
                sub+=m[i][j];
            } 
        }

        
        
    }
    for (int i = 1; i<=N; i++)
    {
        bool a1,a2,a3;
        a1 = e[i];
        if (i < N-1)
        {
            a2 = e[i+1];
            a3 = e[i+2];
        }
        else if (i == N-1)
        {
            a2 = e[i+1];
            a3 = e[1];
            //cout << i<<"   "<<a2 << a3 <<endl;
        }
        else
        {
            a2 = e[1];
            a3 = e[2];
        }

        if (a1&&a2&&a3)
        {
            D++;
        }
    
        // cout << "i = "<<i<<"  ";
        // cout << "e[i] = "<<e[i]<<"  ";
        // cout << "e[((i+1)%(N+1))+1] = "<<e[(i+1)%(N+1)+1]<<"  ";
        // cout << "e[((i+2)%(N+1))+1] = "<<e[(i+2)%(N+1)+1]<<endl;
    
        // else 
        // {
        //     cout << "i = "<<i<<"  ";
        //     cout << a1 <<" "<< a2 <<" "<<a3<<endl;
        // }
    }
    //cout << "e[5] = " <<e[4]<<endl;
    cout <<T<<" "<<E<<" "<<D<<endl;
    return 0;
}
// N = 4
// 1 2 3 4
// e = 3
// e + 1 = 4
// e + 2 = 5
