/*问题描述：给定n个数，请找出其中相差（差的绝对值）最小的两个数，输出它们的差值的绝对值。
输入格式：
　　输入第一行包含一个整数n。
　　第二行包含n个正整数，相邻整数之间使用一个空格分隔。
输出格式：
　　输出一个整数，表示答案。*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int main()
{
    fstream file ("5.txt",ios::in);
    int n;
    int a[1005];
    file >> n;
    //cin >> n;
    for (int i=1; i<=n; i++)
    {
        file >> a[i];
        //cin >> a[i];
    }
    sort(a+1,a+n+1);
    int ans = 9999999;
    for (int i = 1; i<n; i++)
    {
        ans = min(ans,a[i+1]-a[i]);
    }
    cout << ans;
    return 0;
}