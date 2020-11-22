#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
int n,ans=0;
int a[1000005];
int main()
{
    fstream file ("5.txt",ios::in);
    int h,t;
    file >> n;
    //cin >> n;

    for (int i=1; i<=n; i++)
    {
        file >> h >>t;
        //cin >> h >> t;
        for (int j = h + 1; j < t; j++)
        {
            a[j] = 1;
        }
        a[h] = 1;
        a[t] = 2; 
    }
    for (int i=1; i<=n; i++)
    {
        file >> h >> t;
        //cin >> h >> t;
        for (int j=h; j<t; j++)
        {
            if (a[j] == 1&&(a[j+1] == 1 || a[j+1] == 2))
            {
                ans++;
            }
        }
    }
    cout << ans;
    return 0;
}