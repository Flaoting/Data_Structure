#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
typedef struct node
{
    int val;
    int cnt;
}A;

bool cmp(A a, A b)
{
    if(a.cnt > b.cnt)
    {
        return true;
    }
    else if(a.cnt == b.cnt)
    {
        if(a.val < b.val)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    else 
    {
        return false;
    }
}
struct node num[1005];
int n;
int main()
{
    fstream file("9.txt",ios::in);
    int temp;
    file >> n;
    for(int i = 0; i <= 1003; i++ )
    {
        num[i].cnt = 0;
        num[i].val = i;
    }
    for(int i = 1; i <= n; i++)
    {
        file >> temp;
        num[temp].cnt ++;
    }
    sort(num, num+1003, cmp);
    A *p = num;
    while(p->cnt != 0)
    {
        cout << p->val << " "<< p->cnt << endl;
        p++;
    }
    return 0;
}