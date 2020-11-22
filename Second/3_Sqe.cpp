/*输入正整数n、m（m<n），设有n个人坐成一圈，从第1个人开始循环报数，报到m的人出列，
然后再从下一个人开始报数，报到m的人又出列，如此重复，直到所有的人都出列为止。
要求用链式结构和顺序结构实现，按出列的先后顺序输出每个人的信息。*/
#include <iostream>
#include <string.h>
#include "SqeList.h"
using namespace std;
bool map[10005];
int main()
{
    int n = 0, m = 0;
    cin >> n >> m;
    
    int num = 0, p = 1; //p相当于一个指针

    while (num < n)
    {
        register int cnt = 0;
        while(cnt < (m-1))
        {
            if (map[p])     //要是被标记过了，直接跳过
            {
                p++;        //下移一个
                if(p > n)   //要是越界了就循环一个
                {
                    p = 1;
                }
            }
            else 
            {
                cnt++;      //要是没标记过就记数
                p++;
                if (p > n)
                {
                    p = 1;
                }
            }
        }
        //找到了这个数
        while (map[p]) 
        {
            p++;
            if (p > n)
            {
                p = 1;
            }
        }
        num++;
        cout << "The "<<num<<" people is "<< p << endl;
        map[p] = true;
        p++;
        if (p > n)
        {
            p = 1;
        }
    }
    return 0;
}