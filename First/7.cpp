#include <iostream>
using namespace std;
int main()
{
    int n = 0, x = 0, a[200], ans=0, t=0;
    cin >> n >> x;
    for(int i=0; i<=n; i++)
    {
        if (i == 0) 
        {
            a[i] = 1;
        }
        else 
        {
            a[i] = a[i-1]*x;
        }
        cin >> t;
        ans+=a[i]*t;
    }
    cout << ans <<endl;
    return 0;
}
