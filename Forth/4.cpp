#include <iostream>
#include <fstream>
using namespace std;
bool seat[105];     //表示这个座位是否有人
int series[25];        //表示这个排号有几个连续的座位
int n;
int main()
{
    fstream file("4.txt",ios::in);
    file >> n;
    for(int i = 0; i <= 20; i++)
    {
        series[i] = 5;
    }
    int p = 0;
    bool flag = false;
    while (n--)
    {
        file >> p;
        flag = false;
        for (int i = 0; i <20; i++)
        {
            if(series[i] >= p)
            {
                flag = true;
                register int j=1;
                while(seat[i*5+j])
                {
                    j++;
                }
                series[i] -= p;
                int t = 0;
                while( t < p)
                {
                    seat[i*5 + j + t] = true;
                    cout << i*5 + j + t << " ";
                    //cout << "i= "<<i<<" j= "<<j<<" t = "<<t<<endl;
                    t++;
                }
                cout << endl;
                break;
            }
        }
        if (!flag)
        {
            register int t = p;
            for (int i = 1; i <= 100; i++)
            {
                if(!seat[i])
                {
                    seat[i] = true;
                    cout <<i<< " ";
                    t --;
                }
                if(t == 0)
                {
                    break;
                }
            }
            cout << endl;
        }
    }
    return 0;
}