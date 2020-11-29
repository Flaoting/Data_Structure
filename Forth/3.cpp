#include <iostream>
#include <fstream>
using namespace std;
int n,k,t,xl,yd,xr,yu;
int x = 0, y = 0;
int main()
{
    ifstream file("3.txt", ios::in);
    file >> n >> k >> t;
    file >> xl >> yd >> xr >> yu;
    int passby = 0, stay = 0, time = 0;
    bool in = false;
    bool candle = false;
    for(int i = 1; i <= n; i++)
    {
        in = false;
        candle = false;
        time = 0;
        for (int j = 1; j <= t; j++)
        {
            file >> x >> y;
            if(x >= xl && x <= xr && y >= yd && y <= yu)
            {
                in  = true;
                time++;
            }
            else 
            {
                time = 0;
            }
            if(time >= k)
            {
                candle = true;
            }
        }
        if(time >= k)
        {
            candle = true;
        }
        if(candle) 
        {
            stay++;
        }
        if(in)
        {
            passby ++;
        }
    }
    cout << passby <<endl;
    cout << stay;
    return 0;
}
