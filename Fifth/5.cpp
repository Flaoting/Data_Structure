#include <iostream>
using namespace std;
bool map[2005];
int main()
{
    int p = 0,q = 0;
    for (int i = 1; i <= 2000; i++)
    {
        p = i / 10;
        q = i / 100;
        if(i % 7 == 0)
        {
            map[i] = true;
        }
        if((i % 10 == 7) ||(p % 10 == 7)||(q == 7))
        {
            map[i] = true;
        }
        if(i % 100 == 7)
        {
            map[i] = true;
        }
    }
    int n;
    int cnt1 = 0;
    int cnt2 = 0;
    int cnt3 = 0;
    int cnt4 = 0;
    int cnt  = 0;
    cin >> n;
    for (int i = 1; i <= 2000; i++)
    {
        if(cnt == n)
        {
            break;
        }
        if(!map[i])
        {
            cnt++;
        }
        if(map[i])
        {
            if(i % 4 == 0)
            {
                cnt4++;
            }
            if(i % 4 == 1)
            {
                cnt1++;
            }
            if(i % 4 == 2)
            {
                cnt2++;
            }
            if(i % 4 == 3)
            {
                cnt3++;
            }
        }
    }
    cout << cnt1<< endl;
    cout << cnt2<< endl;
    cout << cnt3<< endl;
    cout << cnt4; 
    return 0;
}