#include <iostream>
#include <cstdlib>
using namespace std;
/*
1．编程实现书P12  ADT List 基本操作14个：
（1）用顺序存储结构实现； （2）用链式存储结构实现；
*/

const int LISTINITSIZE = 16;
const int LISTICRESIZE = 8;

typedef struct SqeList
{
    int *pData = NULL;             //动态储存空间的基地址
    int length;             //储存元素个数
    int size;               //当前已分配空间大小
    
}SqeList;

bool InitList(SqeList *L)   //传入的是引用型，用指针来传
{
    L->pData = (int*)malloc(LISTINITSIZE*sizeof(int));
    if(L->pData == NULL) 
    {
        cout << "Floating TIP Memory overflow"<<endl;
        exit(0);
    }
    L->size = LISTINITSIZE;
    L->length = 0;
    cout << "Floating TIP InitList is Successfully runned"<<endl;
    return true;
}

bool CreateList(SqeList *L)

{
    int n;
    //cout << "Please enter the length of this SqeList you want to creat: "<<endl;
    //cin >>n;
    n=10;
    while(n > L->size)
    {
        int *temp;
        temp = (int *)realloc (L->pData,LISTINITSIZE*sizeof(int));
        if (temp == NULL) return false;
        L->pData = temp;
        L->size+=LISTICRESIZE;
        cout <<"Floating TIP L.size has increased and now is "<<L->size<<endl;
    }
    //cout <<"Please enter "<<n<<" elements separated by Spaces :"<<endl;

    int test;
    int ttt[50]={2,2,2,2,3,2,4,5,6,2};
    for (int i=0;i<n;i++)
    {
        //cin >> test;
        //L->pData[i] = test;
        L->pData[i]=ttt[i];
        L->length+=1;
    }
    cout << "Floating TIP CreateList is Successfully runned"<<endl;
    return true;
}

bool DestroyList(SqeList *L)
{
    if(L->pData != NULL )
    {
        free(L->pData);
        L->pData = NULL;
    }
    L->length = 0 ;
    L->size = 0;
    cout << "Floating TIP DestroyList is Successfully runned"<<endl;
    return true;
}

bool ClearList (SqeList *L)
{

    L->length = 0;
    cout << "Floating TIP ClearList is Successfully runned"<<endl;
    return true;
}
//判断是否为一个空表
bool ListEmpty (SqeList L)
{
    
    if (L.length == 0) 
    {
        cout << "Floating TIP ListEmpty is Successfully runned"<<endl;
        return true; //表中元素的长度是0,那么就是一个空表
    }
    cout << "Floating TIP InitList is Successfully runned"<<endl;
    return false;
}

int ListLength(SqeList L)
{
    cout << "Floating TIP ListLength is Successfully runned"<<endl;
    return L.length; //直接返回表的长度
}

bool GetElem (SqeList L,int i,int &e)
{
    if (i<1||i>L.length) return 0;
    e = L.pData[i-1];
    cout << "Floating TIP CreateList is Successfully runned"<<endl;
    return true;
}

//从表中找到e这个元素的位置，并返回他的位置信息
int LocateElem (SqeList L, int e)
{
    for (int i = 0; i < L.length; i ++ )
    {
        if(L.pData[i] == e)
        {
            cout << "Floating TIP LocateElem is Successfully runned"<<endl;
            return i+1;
        }
    }
    return -1;
    //没找到,返回-1
}

//如果cur_e在表L中,而且不是第一个元素，那么通过pre_e返回他前边的一个元素
bool PriorElem (SqeList L, int cur_e,int &pre_e)
{

    for (int i = 1; i < L.length; i ++)
    {
        if (L.pData[i]==cur_e)
        {
            pre_e = L.pData[i-1];
            return true;    
        }
    }
    //如果查找失败，返回False,pre_e不进行操作
    return false;
}

//如果cur_e在表L中,而且不是最后一个元素，那么通过next_e返回他后边的一个元素
bool NextElem (SqeList L, int cur_e,int &next_e)
{
    for (int i = 0; i < L.length - 1; i ++)
    {
        if (L.pData[i]==cur_e)
        {
            next_e = L.pData[i+1];
            return true;    
        }
    }
    //如果查找失败，返回False,pre_e不进行操作
    return false;
}

//在屏幕上打印所有的数据,并用空格隔开，最后输出一个空行
bool ListTraverse (SqeList L)
{
    if(L.pData == NULL || L.length == 0)
    {
        return false;    
    }
    cout << "Floating TIP Traverse this list, element is :";
    for (int i = 0; i < L.length ; i ++) cout << L.pData[i] << " ";
    cout << endl;
    cout << "Floating TIP ListTraverse is Successfully runned"<<endl;
    return true;
}

//将线性表中第i个元素用e代替，并将旧值用e返回
bool SetElem (SqeList *L , int i, int &e)
{   
    if (i < 1 || i>L->length) return false;    //i不在可选的范围内
    
    int temp;
    temp = L->pData[i-1];
    L->pData[i-1] = e;
    e = temp;
    return true;
}

bool InsertElem (SqeList *L, int i, int e)
{
    if (i < 1 || i > L->length + 1) return false;    //i不在可选的范围内
    
    //插入时长度不够,就再申请一点空间
    if (L->length + 1 > L->size)
    {
        int *temp;
        temp = (int *)realloc (L->pData,LISTINITSIZE*sizeof(int));
        if (temp == NULL) return false;
        L->pData = temp;
        L->size+=LISTICRESIZE;
    }
    
    int temp;
    for (int j = L->length ; j > i - 1; j--)
    {
        L->pData[j]=L->pData[j-1];
    }
    L->pData[i-1] = e;
    L->length +=1;
    return true;

}

bool DeleteElem (SqeList *L, int i, int &e)
{
    
    if (i < 1 || i>L->length) return false;    //i不在可选的范围内

    e = L->pData[i-1];
    for (int j = i - 1; j < L->length-1;j++)
    {
        L->pData[j] = L->pData[j+1];
        
    }    
    L->length --;
    return true;
}

/*
int main()

{
    SqeList L;
    int i,e,temp,location=-1;
    InitList(&L);
    CreateList(&L);
    ListTraverse(L);
    e=666,i=3,temp=999;
    cout << "Floating TIP Before getting element e is "<<e<<endl;
    cout << "Floating TIP Now get element locate in "<<i<<endl;
    GetElem(L,i,e);
    cout << "Floating TIP After getting element e is "<<e<<endl;
    
    cout << "Floating TIP Before getting element before e temp is "<<temp<<endl;
    PriorElem(L,e,temp);
    cout << "Floating TIP After getting element before e temp is "<<temp<<endl;
    
    cout << "Floating TIP Before getting element next e temp is "<<temp<<endl;
    NextElem(L,e,temp);
    cout << "Floating TIP After getting element next e temp is "<<temp<<endl;
    
   
    cout << "Floating TIP e is "<<e<<endl;
    location = LocateElem(L,e);
    cout << "Floating TIP e's location is "<< location <<endl;
    if (ListEmpty(L))
        cout << "Floating TIP L is empty "<<endl;
    else 
        cout << "Floating TIP L is unempty "<<endl;
    cout << "Floating TIP the length of L is "<<ListLength(L)<<endl;
    cout << "Floating TIP Now we will clear the list L"<<endl;
    //ClearList(&L);
    //cout << "Floating TIP After clear, the length of L is "<<ListLength(L)<<endl;
    
    cout << "Floating TIP Now L is  "<<ListTraverse(L)<<endl;
    cout <<"Floating TIP set "<<temp<<" at the location of "<<i<<endl;
    SetElem(&L,i,temp);
    ListTraverse(L);
    InsertElem(&L,5,888);
    ListTraverse(L);
    cout << "Floating TIP now we will delete the third location 3"<<endl;
    DeleteElem(&L,3,e);
    ListTraverse(L);
    return 0;
}
*/