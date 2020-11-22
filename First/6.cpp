#include <iostream>
using namespace std;

long long binpow(long long a, long long b) 
{
    long long res = 1;
    while (b > 0)
    {
    if (b & 1) res = res * a;
    a = a * a;
    b >>= 1;
    }
    
    return res;
}
long long factorial(long long n)
{
    long long ans = 1;
    for (int i=1;i<=n;i++)  ans*=i;
    return ans;
}
int main()
{
    long long a[256];
    for (int i=0;i<=20;i++)
    {
        a[i]=factorial(i)*binpow(2,i);
        cout <<a[i]<<endl;
    }
    return 0;
}