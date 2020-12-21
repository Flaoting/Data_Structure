#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

typedef struct node
{
    int key;
    int start;
    int length;
    int end;
}T;

bool cmp(T a, T b)
{
    return a.key < b.key;
}

int N,K;
int keybox[2010];
bool flag[2010];
struct node teacher[2010];

void read()
{
    //fstream file("14.txt",ios::in);
    int start,length,key;
    cin >> N >> K;
    for(int i = 1; i <= N; i++)
    {
        flag[i] = true;   //有钥匙
        keybox[i] = i; //钥匙按位就班
    }

    for(int i = 1; i <= K; i++)
    {
        cin >> key >> start >> length;
        teacher[i].key = key;
        teacher[i].start = start;
        teacher[i].length = length;
        teacher[i].end = start + length;
    }
    return ;
}
void print()
{
    cout << keybox[1];
    for(int i = 2;i <= N; i++) 
    {
        cout <<" "<< keybox[i];
    }
}

void borrow()
{

    sort(teacher + 1, teacher + K + 1, cmp);
    for(int i = 1; i <= 21111; i++)
    {
        for(int j = 1; j <= K; j ++)
        {
            if(teacher[j].end == i)    //还钥匙
            {
                for(int k = 1; k <= N; k ++)
                {
                    if(!flag[k])  
                    {
                        keybox[k] = teacher[j].key;
                        flag[k] = true;
                        break;
                    }
                }
            }
        }

        for(int j = 1; j <= K; j++)
        {
            if(teacher[j].start == i)   //借钥匙
            {
                for(int k = 1; k <= N; k++)
                {
                    if(flag[k] && teacher[j].key == keybox[k])
                    {
                        flag[k] = false;
                    }
                }
            }  
        }
    }
    return ;
}

int main()
{
    read();
    borrow();
    print();
    return 0;
}
