#include <iostream>
#include <cstdlib>
using namespace std;
typedef struct node
{
    int x;
    int y;
    int flag;
    int value; 
}Point;
int n;
Point spot[1005];
int ans[5];
bool check(Point &p)
{
    for(int i = 1; i <= n ;i++)
    {
        if(spot[i].x == p.x - 1 && spot[i].y == p.y)
        {
            p.flag ++;
        }
        if(spot[i].x == p.x + 1 && spot[i].y == p.y)
        {
            p.flag ++;
        }
        if(spot[i].x == p.x && spot[i].y == p.y - 1)
        {
            p.flag ++;
        }
        if(spot[i].x == p.x && spot[i].y == p.y + 1)
        {
            p.flag ++;
        }
        if(spot[i].x == p.x - 1 && spot[i].y == p.y - 1)
        {
            p.value ++;
        }if(spot[i].x == p.x + 1 && spot[i].y == p.y + 1)
        {
            p.value ++;
        }if(spot[i].x == p.x - 1 && spot[i].y == p.y + 1)
        {
            p.value ++;
        }if(spot[i].x == p.x + 1 && spot[i].y == p.y - 1)
        {
            p.value ++;
        }
    }
    if(p.flag == 4) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}
int main()
{
    //freopen("5.txt","r",stdin);
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> spot[i].x >> spot[i].y;
    }
    for(int i = 1; i <= n; i++)
    {
        if(check(spot[i]))
        {
            ans[spot[i].value] ++;
        }
    }
    for(int i = 0; i < 5; i++)
    {
        cout << ans[i] <<endl;
    }
    return 0;
}