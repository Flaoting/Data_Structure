#include <iostream>
using namespace std;
int main()
{
    int a[100];
    int n;
    cin >> n;
    for (int i=1;i<=n;i++) cin>>a[i];
    int p=0;//p 指向当前应填补的空位
    bool flag;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=i;j++)
        {
            if(j==i&&flag)
            {
                a[p]=a[i];
                p++;
                break;
            }
            if(a[i]==a[j]&&i!=j)
            {
                if(p==0)
                {
                    p=i;
                    flag=1;
                }
                break;
            }
            
        }
    }
    for (int i=1;i<p;i++) cout <<a[i]<<" ";
}

