/*8、排序算法比较 （必做）（排序）
[问题描述]
利用随机函数产生10个样本，每个样本有50000个随机整数（并使第一个样本是正序，第二个样本是逆序），利用直接插入排序、希尔排序，冒泡排序、快速排序、选择排序、堆排序，归并排序、基数排序8种排序方法进行排序（结果为由小到大的顺序），并统计每一种排序算法对不同样本所耗费的时间。
 [基本要求]
（1） 原始数据存在文件中，用相同样本对不同算法进行测试；
（2） 屏幕显示每种排序算法对不同样本所花的时间；
*/

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
using namespace std;

bool cmp(const int& a, const int& b)
{
    return a > b;
}

void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
    return;
}

void Generate_random_sample()
{
    string fileName;
    fstream file;
    stringstream order;
    int *num1, *num2;
    num1 = (int*)malloc(sizeof(int) * 50010);
    num2 = (int*)malloc(sizeof(int) * 50010);
    for (int i = 3; i <= 10; i++)
    {
        order << i;
        fileName = order.str() + ".txt";
        cout << fileName << " " << i << " " << order.str() << endl;
        file.open(fileName.c_str(), ios::out);
        if (!file)
        {
            cout << fileName << "can't be opened, please check it ！" << endl;
            exit(0);
        }
        srand((unsigned int)time(NULL));

        for (int j = 1; j <= 50000; j++)
        {
            file << rand() << " ";
            if (j % 25 == 0)
            {
                file << endl;
            }
        }

        order.str("");
        file.close();
    }

    srand((unsigned int)time(NULL));

    for (int i = 1; i <= 50000; i++)
    {
        num1[i] = rand();
        num2[i] = num1[i];
    }
    sort(num1 + 1, num1 + 50000 + 1);  //正序
    sort(num2 + 1, num2 + 50000 + 1, cmp);  //逆序

    file.open("1.txt", ios::out);

    for (int i = 1; i <= 50000; i++)
    {
        file << num2[i] << " ";
        if (i % 25 == 0)
        {
            file << endl;
        }
    }
    file.close();

    file.open("2.txt", ios::out);
    for (int i = 1; i <= 50000; i++)
    {
        file << num1[i] << " ";
        if (i % 25 == 0)
        {
            file << endl;
        }
    }
    file.close();

    return;
}

void show(int a[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}

//a is the array, n is number, and first is 1

void Insertion_sort(int a[], int n)
{
    int j = 0, temp = 0;
    for (int i = 2; i <= n; i++)
    {
        j = i;
        temp = a[i];

        while (j > 1 && a[j - 1] > temp)
        {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = temp;
    }
}

//d is interval 
void ShellInsertSort(int a[], int n, int d)
{
    int temp, j;
    for (int i = d + 1; i <= n; i++)
    {
        if (a[i] < a[i - d])
        {
            temp = a[i];
            for (j = i; j > d; j = j - d)
            {
                if (temp < a[j - d])
                {
                    a[j] = a[j - d];
                }
                else
                {
                    break;
                }
            }
            a[j] = temp;
        }
    }
}

void Shell_sort(int a[], int n)
{
    for (int i = 5; i >= 1; i -= 2)
    {
        ShellInsertSort(a, n, i);
        //cout << i<<end
    }
    return;
}

void Bubble_sort(int a[], int n)
{
    for (int i = n; i > 1; i--)
    {
        for (int j = 1; j < i; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
    return;
}

int Partition(int a[], int low, int high)
{
    int temp = a[low];
    while (low < high)
    {
        while (low < high && a[high] >= temp)
        {
            high--;
        }
        a[low] = a[high];
        while (low < high && a[low] <= temp)
        {
            low++;
        }
        a[high] = a[low];
    }
    a[low] = temp;
    return low;
}

void Qsort(int a[], int low, int high)
{
    int pivotloc;
    if (low < high)
    {
        pivotloc = Partition(a, low, high);
        Qsort(a, low, pivotloc - 1);
        Qsort(a, pivotloc + 1, high);
    }
    return;
}

void Quick_sort(int a[], int n)
{
    Qsort(a, 1, n);
    return;
}

void Selection_sort(int a[], int n)
{
    int k, temp;
    for (int i = 1; i <= n; i++)
    {
        k = i;
        for (int j = i + 1; j <= n; j++)
        {
            if (a[k] > a[j])
            {
                k = j;
            }
        }
        if (i != k)
        {
            swap(a[i], a[k]);
        }
    }
    return;
}

void HeapAdjust(int a[], int low, int high) 
{
    int temp = a[low];
    int i = low, j = i*2;
    while (i < low) 
    {
        if(j + 1 < high && a[j] < a[j+1]) 
        {
            j++;
        }
        //在左右子树里边选择大的，j指向这个

        if(temp >= a[j])
        {
            break;
        }
        //已经是大顶堆,结束这次循环

        a[i] = a[j];
        i = j;
        j = 2 * i;
    }
    a[i] = temp;    
    return;
}
//HeapAdjust

void HeapSort(int a[], int n)
{
    for(int j = n/2; i > 0; i--)
    {
        HeapAdjust(a,i,n);  //从下往上调整一遍
    }

    for(int i = n; i > 1; i--)
    {
        swap(a[1],a[i]);
        HeapAdjust(a,1,i-1);
    }
    return;
}


bool FetchData(int a[], int i)
{
    string fileName;
    fstream file;
    stringstream order;

    order << i;
    fileName = order.str() + ".txt";
    //cout << fileName<<" " << i <<" "<<order.str()<<endl;
    file.open(fileName.c_str(), ios::in);
    if (!file)
    {
        cout << fileName << "can't be opened, please check it ！" << endl;
        exit(0);
    }
    for (int j = 1; j <= 50000; j++)
    {
        if (file.eof())
        {
            return false;
        }
        file >> a[j];
    }
    return true;
}
//取出第i个文件存放的数据,50000个都取出来

bool OneFunctionTime(void (*p)(int*, int))
{
    int *a;
    a = (int*)malloc(sizeof(int) * 50010);
    int n = 50000;
    clock_t start, end;
    for (int i = 1; i <= 10; i++)
    {
        start = clock();
        FetchData(a,i);
        p(a, 50000);
        end = clock();
        show(a, 100);
        cout << i << ".txt costs " << end-start << endl;
    }
    return true;
}

void DisplayCaculationTime()
{

    void (*pfun)(int*, int);
    pfun = NULL;    //pfun is a function pointer
    
    /*cout << "-------------------------------------------------------------" << endl;
    cout << "QuickSort" << endl;
    pfun = Quick_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "SelectionSort" << endl;
    pfun = Selection_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "InsertationSort" << endl;
    pfun = Insertion_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;
    
    cout << "-------------------------------------------------------------" << endl;
    cout << "ShellSort" << endl;
    pfun = Shell_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;*/

    cout << "-------------------------------------------------------------" << endl;
    cout << "BubbleSort" << endl;
    pfun = Bubble_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;



}

int main()
{

    /*int a[30] = {-1, 10,9,8,7,6,5,4,3,2,1 };
    show(a, 10);
    Bubble_sort(a, 10);
    show(a, 10);*/
    //Generate_random_sample();
    DisplayCaculationTime();
    return 0;
}







