#include <iostream>
#include <fstream>
using namespace std;
int n=0,k=0;
int a[10005];
int main()
{
    fstream file("4.txt",ios::in);
    file >> n >>k;
    //cin >> n >> k; 
    int ans=0;
    for (int i = 1; i<=n; i++ )
    {
        file >> a[i];
        //cin >> a[i];
    }
    int cnt=0,temp=0;
    while(cnt <= n)
    {
        temp += a[cnt];
        if (temp>=k)
        {
            ans++;
            temp=0;
        }
        cnt++;
    }
    if (temp != 0) ans++;
    cout << ans;
    return 0;
}