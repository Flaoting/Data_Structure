/*4、Huffman编码与解码 (必做)（Huffman编码、二叉树）
[问题描述]
对一篇不少于5000字符的英文文章（source.txt），统计各字符出现的次数，实现Huffman编码(code.dat)，以及对编码结果的解码(recode.txt)。
[基本要求]
（1） 输出每个字符出现的次数和编码,并存储文件(Huffman.txt)。
（2） 在Huffman编码后，英文文章编码结果保存到文件中(code.dat)，编码结果必须是二进制形式，即0 1的信息用比特位表示，不能用字符’0’和’1’表示。
（3） 实现解码功能。
*/
/*实现对ASCII码 32~126 这95个字符的编码，他们的权重由在源文件中出现的频率决定，首先读取文件，计算每个ASCII码对应的权重，*/

#include <iostream>
#include <fstream>
#include <malloc.h>
#include <string>
using namespace std;
#define MAX_VALUE 2222222
#define MaxBit 10
typedef struct HTNode
{
    int weight;
    int parent, lchild, rchild;
    bool flag;  //对树合并时进行标记
}HTNode,*HufTree;

typedef struct Code   //存放哈夫曼编码的数据元素结构
{
    char data;      //存入字符数据
    int bit[MaxBit];//数组
    int start;//编码的起始下标
    int weight;//字符的权值
}HufCode;

void CaculateWeightAndSaveFile(int *weight, string inName, string outName)
{
    //对ASCII码在32~126的可显示码进行统计
    fstream inFile(inName.c_str(), ios::in);
    fstream outFile(outName.c_str(), ios::out);
    if(!inFile)
    {
        throw "Floating TIP   In the function void CaculateWeightAndSaveFile()  File " + inName + " can't be opened , please check it. ";
    }
    
    for(int i = 0; i < 95; i++)
    {
        weight[i] = 0;
    }

    char ch = 'A'; 

    while (!inFile.eof())
    {
        ch = inFile.get();

        if(ch >= 32 && ch <= 126)
        {
            weight[ch - 32]++;
        }
    }

    for(int i = 0; i < 95; i++)
    {
        outFile << (char)(i + 32) << " " << weight[i]<<endl;
        //cout << (char)i << " " << weight[i]<<endl;
    }

    inFile.close();
    outFile.close();
    return;
}

void readFrequency(int &n, HufCode code[], string frequencyFileName)  //个数 编码数组 文件名
{
    fstream file(frequencyFileName.c_str(),ios::in);
    if(!file)
    {
        throw "Floating TIP   In the function void readFrequency()  File " + frequencyFileName + " can't be opened , please check it. ";
    }
    for (int i = 1; i <= n; i++)
    {
        file >> code[i].data >> code[i].weight;
    }
    file.close();
    return;
}

void initHufTree(HufTree &HT,int n,int *w)
{
    for(int i = 1; i <= 2*n - 1; i++)
    {
        if(i <= n)
        {
            HT[i].weight = w[i];
        }
        else
        {
            HT[i].weight = 0;
        }
        HT[i].parent = 0;
        HT[i].flag = false;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
}

void CreateHufTree(HufTree &HT, int n, int *w)
{
    if(n <= 0) 
    {
        return ;
    }
    HT = (HufTree)malloc(sizeof(HTNode)*2*n + 10);
    int x1,x2;
    int w1,w2;
    for(int i = 1; i <= n-1; i++)
    {
        x1 = 1;
        x2 = 1;
        w1 = MAX_VALUE;
        w2 = MAX_VALUE;

        for(int j = 1; j <= n+i; j++)
        {
            if(HT[j].weight< w1 && !HT[j].flag)
            {
                w2 = w1;
                x2 = x1;
                x1 = j;
                w1 = HT[j].weight;
            }
            else if(HT[j].weight < w2 && !HT[j].flag)
            {
                x2 = j;
                w2 = HT[j].weight;
            }
        }

        HT[n + i].lchild = x1;
        HT[n + i].rchild = x2;
        HT[n + i].weight = HT[x1].weight + HT[x2].weight;
        HT[x1].parent = n + i;
        HT[x2].parent = n + i;
        HT[x1].flag = true;
        HT[x2].flag = true;
    }
    return;
}
//建立霍夫曼树

void CaculateHufCoding(HufTree HT, HufCode HufTable[], int n)  //Tree ,霍夫曼编码表 n个节点
{
    HufCode *cd = (HufCode*)malloc(sizeof(HufCode));
    int child, parent;  //临时变量

    for(int i = 1; i <= n; i ++)
    {
        cd->start = 0;
        cd->weight = HT[i].weight;
        child = i;
        parent = HT[child].parent;

        while(parent != 0)  //向上寻找,直到找到根节点
         {
            if(HT[parent].lchild == child)
            {
                cd->bit[cd->start] = 0;     //左边是0
            }
            if(HT[parent].rchild == child)
            {
                cd->bit[cd->start] = 1;     //右边是1
            }
            cd->start ++;
            child = parent;
            parent = HT[parent].parent;
        }
    }
}

void ShowHufTree(HufTree &BT)
{

}

int main()
{

    int N;
    int weight[256];
    string inFileName = "E://vscode//C++//Data_structure//Cours_Design//Sourse//source.txt";
    string outFileName = "E://vscode//C++//Data_structure//Course_Design//Sourse//Huffman.txt";
    try
    {
        CaculateWeightAndSaveFile(weight, inFileName, outFileName);
    }catch (string ss)
    {
        cout << ss <<endl;
    }

    //HufTree HT;
    //read(N,weight);
    //CreateHufTree(HT, N ,weight);
    return 0;
}








// void print(HuTree ht[],int curr,int depth){
// 	int i;
// 	for(i=1;i<=depth;++i)
// 		printf("  |");
// 	if(ht[curr].leaf){
// 		if(ht[curr].leaf->c==' ')//将空格换成|_表示
// 			printf("|_");
// 		else if(ht[curr].leaf->c=='/n')//将回车换成_|表示
// 			printf("_|");
// 		else
// 			printf("%c ",ht[curr].leaf->c);
// 	}
// 	else
// 		printf("[]");
// 	printf("|");
// 	for(i=depth+2;i<=25;++i)
// 		printf("  |");
// 	printf("/n");
// }

// void PrintHuTree(HuTree ht[],int c_num){
// 	int curr=2*c_num-1, pos[199], depth=0, i=0, temp, st[199], flag=0, pre=curr;
// 	pos[pre]=0;
// 	printf("/nPrinting the Huffman Tree*******************************************************/n");
// 	printf("/n[] represents the node which is not a leaf node.|_ represents SPACE._| represents ENTER./n/n");
// 	printf(" 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|/n");//树的深度
// 	while(i!=0||curr!=0||flag==0)
//     {
// 		flag=1;
// 		while(curr){
// 			st[++i]=curr;
// 			if(pre!=curr)
// 				pos[curr]=pos[pre]+1;
// 			pre=curr;
// 			curr=ht[curr].rchild;
// 		}
// 		temp=st[i--];
// 		print(ht,temp,pos[temp]);
// 		if(ht[temp].lchild){
// 			curr=ht[temp].lchild;
// 			pos[curr]=pos[temp]+1;
// 			pre=curr;
// 		}
// 	}
// }


/*
我方老板  :pjh
秘书     :pln
助理     :rxy
对方老板 :tj


*/