#pragma comment(linker, "/STACK:10240000000,10240000000")
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
    int* num1, * num2;
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
    int k;
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
    int i = low, j = i * 2;
    while (j < high)
    {
        if (j + 1 < high && a[j] < a[j + 1])
        {
            j++;
        }
        //在左右子树里边选择大的，j指向这个

        if (temp >= a[j])
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

void Heap_sort(int a[], int n)
{
    for (int i = n / 2; i > 0; i--)
    {
        HeapAdjust(a, i, n);  //从下往上调整一遍
    }

    for (int i = n; i > 1; i--)
    {
        swap(a[1], a[i]);
        HeapAdjust(a, 1, i - 1);
    }
    return;
}

void MergeOneTime(int a[], int b[], int i, int m, int n)
{
    int j, k;
    for (j = m + 1, k = i; i <= m && j <= n; k++)
    {
        if (a[i] < a[j])
        {
            b[k] = a[i];
            i++;
        }
        else
        {
            b[k] = a[j];
            j++;
        }
    }
    while (i <= m)
    {
        b[k++] = a[i++];
    }
    while (j <= n)
    {
        b[k++] = a[j++];
    }
    return;
}
//一趟归并，把a[i,m],a[m+1,n],归并为有序的b[i,n]

void Msort_Re(int a[], int b[], int s, int t)
{
    int* c;
    c = (int*)malloc(sizeof(int) * (t - s) + 10);
    if (s == t)
    {
        b[s] = a[s];
    }
    else
    {
        int mid = (s + t) / 2;
        Msort_Re(a, c, s, mid);
        Msort_Re(a, c, mid + 1, t);
        MergeOneTime(c, b, s, mid, t);
    }
    return;
}
//递归进行归并排序a[s,t],并入到b[s,t]

void MergeSort(int a[], int n)
{
    Msort_Re(a, a, 1, n);
    return;
}
//归并排序

void MergePass(int a[], int b[], int k, int n)
//k为当前子序列的长度
{
    int i, j;
    for (i = 1; i <= n - 2 * k + 1; i += k * 2) 
    {
        MergeOneTime(a, b, i, i + k - 1, i + 2 * k - 1);
    }
    if (i + k < n)
    {
        MergeOneTime(a, b, i, i + k - 1, n);
    }
    else 
    {
        for (j = i; j <= n; j++) 
        {
            b[j] = a[j];
        }
    }
    return;
}
//k是要一个子序列的长度，n是总长度

void Merge_sort(int a[], int n)
{
    int k = 1;
    int* b = (int*)malloc(sizeof(int) * n + 10);
    while (k < n)
    {
        MergePass(a, b, k, n);
        k *= 2;
        MergePass(b, a, k, n);
        k *= 2;
    }
    free(b);
    return;
}


int CaculateMaxBit(int a[], int n)
{
    int maxnum = a[1], maxbit = 0;
    for (int i = 2; i <= n; i++)
    {
        if (maxnum < a[i])
        {
            maxnum = a[i];
        }
    }
    while (maxnum)
    {
        maxbit++;
        maxnum /= 10;
    }
    return maxbit;
}
//求出一组数据最大位数的函数

int GetSpecifiedBit(int num, int d)
{
    int pow = 1;
    d--;
    while (d > 0)
    {
        pow *= 10;
        d--;
    }
    num /= pow;
    num %= 10;
    return num;
}
//取出数字num第d位的数字(注意是 从右向左数)


typedef struct node
{
    int data;
    struct node* next;
}RadixNode;

void Radix_sort(int a[], int n)
{
    if (n <= 1)
    {
        return; //就一个或者零个数，还排个屁啊
    }
    RadixNode* front[10], * rear[10], * head, * tail = NULL, * p = NULL; //十个队列的队头和队尾的指针
    int max_bit, temp;
    max_bit = CaculateMaxBit(a, n);  //找出最大的位数,这决定了要进行几次的收集和发放
    head = (RadixNode*)malloc(sizeof(RadixNode));
    head->data = -1;
    head->next = NULL;
    p = head;
    for (int i = 1; i <= n; i++)
    {
        p->next = (RadixNode*)malloc(sizeof(RadixNode));
        p = p->next;
        p->data = a[i];
        p->next = NULL;
    }//这样就建造好了一条链子  
    for (int j = 1; j <= max_bit; j++)
    {
        for (int k = 0; k < 10; k++)
        {
            front[k] = NULL;
            rear[k] = NULL;
        }
        //初始化
        p = head->next;
        while (p != NULL)
        {
            temp = GetSpecifiedBit(p->data, j);
            if (front[temp] == NULL)
            {
                front[temp] = p;
                rear[temp] = p;
            }
            else
            {
                rear[temp]->next = p;
                rear[temp] = p;
            }
            p = p->next;

        }
        //断裂这条链子，然后放到桶中
        head->next = NULL;
        tail = NULL;
        for (int i = 0; i < 9; i++)
        {
            if (front[i] != NULL)
            {
                if (head->next == NULL)
                {
                    head->next = front[i];
                    tail = rear[i];
                    continue;
                }
                else
                {
                    tail->next = front[i];
                    tail = rear[i];
                }
            }
        }
        tail->next = NULL;
        //从前到后进行收集
    }
    p = head->next;
    for (int i = 1; i <= n && p != NULL; i++, p = p->next)
    {
        a[i] = p->data;
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
    int* a;
    int sum_time = 0;
    double av = 0;
    a = (int*)malloc(sizeof(int) * 50010);
    int n = 50000;
    clock_t start, end;
    for (int i = 1; i <= 10; i++)
    {
        start = clock();
        FetchData(a, i);
        p(a, 50000);
        end = clock();
        //show(a, 10);
        cout << i << ".txt costs " << end - start << endl;
        sum_time += (end - start);
    }
    av = sum_time / 10;
    cout << "The total time consumed by these ten samples " << sum_time << endl;
    cout << "The average time used for these ten samples " << av << endl;
    return true;
}

void DisplayCaculationTime()
{

    void (*pfun)(int*, int);
    pfun = NULL;    //pfun is a function pointer

    cout << "-------------------------------------------------------------" << endl;
    cout << "InsertationSort" << endl;
    pfun = Insertion_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "ShellSort" << endl;
    pfun = Shell_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "HeapSort" << endl;
    pfun = Heap_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "RadixSort" << endl;
    pfun = Radix_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
    cout << "MergeSort" << endl;
    pfun = Merge_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;

    cout << "-------------------------------------------------------------" << endl;
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
    cout << "BubbleSort" << endl;
    pfun = Bubble_sort;
    OneFunctionTime(pfun);
    cout << "-------------------------------------------------------------" << endl;

}

int main()
{
    //Generate_random_sample();
    DisplayCaculationTime();
    return 0;
}

