/*4、Huffman编码与解码 (必做)（Huffman编码、二叉树）
[问题描述]
对一篇不少于5000字符的英文文章（source.txt），统计各字符出现的次数，实现Huffman编码(code.dat)，以及对编码结果的解码(recode.txt)。
[基本要求]
（1） 输出每个字符出现的次数和编码,并存储文件(Huffman.txt)。
（2） 在Huffman编码后，英文文章编码结果保存到文件中(code.dat)，编码结果必须是二进制形式，即0 1的信息用比特位表示，不能用字符’0’和’1’表示。
（3） 实现解码功能。
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
using namespace std;
#define MAX_VALUE 2222222
#define MaxBit 10

typedef struct HTNode
{
    int weight;
    int parent, lchild, rchild;
    bool flag;  //对树合并时进行标记
}HTNode, * HufTree;

typedef struct FileInfo		//文件信息类,对应一个字符
{
    unsigned char ch;	//这个字符
    int count;			//出现的次数
    string hufcode;		//对应的霍夫曼编码
    bool operator <(const FileInfo &a)		//重载小于号
	{
		return this->count < a.count;
	}
}FileInfo;

class HufOperate
{
private:
    HufTree HT;
    FileInfo exist[128];    //存在于文件中ASCII码的信息
    int length;
public:
	HufOperate();
	~HufOperate();

    void read(string inName, string outName);
    //根据文件名读取并储存文件信息(source.txt Huffman.txt)

    void initHufTree();
    //初始化霍夫曼树
    
    void CreateHufTree();
    //建立霍夫曼树
    
    void CodeHufCode();
    //根据霍夫曼树进行编码

    bool Compress(const string inName, const string outName);
    //文件压缩

    void Rebuild();
    //重新建树和编码

    void DeCodeFile();
    //解压文件
};

HufOperate::HufOperate()
{
    this->HT = NULL;
    this->length = 0;
}

HufOperate::~HufOperate()
{
}

void HufOperate::read(string inName, string outName)
{
    fstream inFile(inName.c_str(), ios::in);
    if (!inFile)
    {
        throw "File " + inName + " can't be opened , please check it. ";
        return;
    }
    int weight[128];

    for (int i = 0; i < 128; i++) 
    {
        weight[i] = 0;
    }
    char ch = 'A';
    int c = 0;
    while (!inFile.eof())
    {
        ch = inFile.get();
        if (ch >= 32 &&ch <= 127) 
        {
            if (weight[ch] == 0)
            {
                this->length++; //统计出现字符的个数
            }
            weight[ch]++;
            c++;
        }
    }
    inFile.close();
    cout << "共计" << c << "个字符" << endl;
    cout << "共计" << this->length << "种字符" << endl;
    fstream outFile(outName.c_str(), ios::out);

    int cnt = 1;
    for (int i = 1; i < 128; i++)
    {
        if (weight[i] != 0)
        {
            outFile << (char)(i) << " " << weight[i] << endl;
            exist[cnt].ch = i;
            exist[cnt].count = weight[i];
            cnt++;
        }
    }
    outFile.close();
    return;
}

void HufOperate::initHufTree( )
{
    for (int i = 1; i <= 2 * length - 1; i++)   //对这2n-1个结点进行初始化
    {
        if (i <= length)            //要是叶子的话，对权值进行初始化
        {
            HT[i].weight = this->exist[i].count;
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
    return;
}

void HufOperate::CreateHufTree()
{
    if (length <= 0)
    {
        return;
    }

    HT = (HufTree)malloc(sizeof(HTNode) * 2 * length );
    initHufTree();  //初始化

    int x1, x2;
    int w1, w2;
    int n = length;

    for (int i = n + 1; i <2 * n; i++)
    {
        x1 = 1;
        x2 = 1;
        w1 = MAX_VALUE;
        w2 = MAX_VALUE;
        for (int j = 1; j <= i - 1; j++)
        {
            if (HT[j].weight < w1 && !HT[j].flag)
            {
                w2 = w1;
                x2 = x1;
                x1 = j;
                w1 = HT[j].weight;
            }
            else if (HT[j].weight < w2 && !HT[j].flag)
            {
                x2 = j;
                w2 = HT[j].weight;
            }
        }
        HT[i].lchild = x1;
        HT[i].rchild = x2;
        HT[i].weight = HT[x1].weight + HT[x2].weight;
        HT[x1].parent = i;
        HT[x2].parent = i;
        HT[x1].flag = true;
        HT[x2].flag = true;
        //选出两个最小的结点，放到的单元格里
        //cout << HT[x1].weight<< "  " << HT[x2].weight << "  "<<HT[i].weight<<endl;
    }
    return;
}

void HufOperate::CodeHufCode()
{
    string temp;
    for (int i = 1; i <= length; i++) 
    {
        temp = "";
        for (int j = i, f = HT[i].parent; f != 0; j = f, f = HT[f].parent)
        {
            if (HT[f].lchild == j)      //左孩子为0
            {
                temp += "0";
            }
            else                        //右孩子为1
            {
                temp += "1";
            }
        }
        reverse(temp.begin(), temp.end());
        this->exist[i].hufcode = temp;
        //cout <<this->exist[i].count<<"  "<< this->exist[i].hufcode << endl;
    }
    return;
}

bool HufOperate::Compress(const string filename, const string outName)
{
    //1.打开一个文件，统计文件字符出现的次数
    //2.生成对应的哈弗曼编码
    //3.压缩文件
    //4.写配置文件，方便解压缩

    read(filename, outName);    //读出数据
    CreateHufTree();            //建树
    CodeHufCode();              //编码
    
    string compressFile = "code.dat";
    //压缩后的文件名 
    FILE* file = fopen(filename.c_str(), "rb");
    FILE* finCompress = fopen(compressFile.c_str(), "wb"); 

    char ch = fgetc(file);
    unsigned char inch = 0;
    int index = 0,ht_index;  //一个字节的八位

    while (!feof(file))
    {
        ht_index = 32;
        for (int i = 1; i <= length; i++)
        {
            if (this->exist[i].ch == ch)
            {
                ht_index = i;
            }
        }
        string& code = this->exist[ht_index].hufcode;

        for (int i = 0; i < code.size(); i++)
        {
            inch <<= 1;     //低位向高位进
            if (code[i] == '1')
            {
                inch |= 1;  //这一位是1的话就存1
            }

            if (++index == 8)
            {
                fputc(inch, finCompress); //够8位，装进文件
                index = 0;   //重新一轮开始
                inch = 0;
            }
        }
        ch = fgetc(file);
    }

    fclose(file);

    //如果index = 0 说明 上边8位刚好存满 不等 下一个自己又出来了
    if (index != 0)   //处理最后一个字符不够的问题
    {
        inch <<= (8 - index); //最高位必须装上 后边的浪费掉
        fputc(inch, finCompress);
    }

    fclose(finCompress);
    return true;
}

void HufOperate::Rebuild()
{
    fstream file("Huffman.txt", ios::in);
    if (!file)
    {
        cout << "Huffman.txt can't be opened " << endl;
        return;
    }
    int cnt = 1;
    char ch;
    int fre = 0;
    while (!file.eof())
    {
      
        ch = file.get();
        file >> fre;
        file.ignore();
        if (ch >= 32 && ch <= 127)
        {
            this->exist[cnt].ch = ch;
            this->exist[cnt].count = fre;
            cnt++;
            this->length++;
        }
    }
    CreateHufTree();            //建树
    CodeHufCode();              //编码
}

void HufOperate::DeCodeFile( ) 
{

    //原压缩文件
    string inName = "code.dat";
    string outName = "recode.txt";

    FILE* file = fopen(inName.c_str(), "rb");
    FILE* out = fopen(outName.c_str(), "w");
    if (!file)
    {
        cout << "文件 " << inName << "打开失败" << endl;
    }
    int pos = 8, ptr = 2*length-1;
    char ch = fgetc(file);

    while (!feof(file)) 
    {
        ptr = 2 * length - 1;
        while (HT[ptr].lchild != -1 || HT[ptr].rchild != -1)
        {
            pos--;
            unsigned char temp = ch >> pos;
            int cur = 1 & temp;
            if (cur == 0)
            {
                ptr = HT[ptr].lchild;
            }
            if (cur == 1)
            {
                ptr = HT[ptr].rchild;
            }
            if (pos == 0)
            {
                ch = fgetc(file);
                pos = 8;
            }
        }
        cout << this->exist[ptr].ch;
        fputc(this->exist[ptr].ch, out);
    }
    return;
}

int main()
{
    HufOperate H1,H2;
    string s1 = "source.txt";
    string s2 = "Huffman.txt";
    char cc;
    cout << "----------欢迎使用霍夫曼编码压缩系统--------------" << endl;
    cout << "请删除文件夹内多余文件，只保留要压缩的文件source.txt" << endl;
    cout << "即将开始压缩，任意按键继续....";
    cc = getchar();
    cout << endl << "数据统计如下 ： " << endl;
    H1.Compress(s1, s2);
    cout << endl;
    cout << "压缩完毕，请验证压缩文件后删除源文件source.txt" << endl;
    cout << "即将开始解压，任意按键继续...";
    cc = getchar();
    H2.Rebuild();
    H2.DeCodeFile();
    cout << "解压成功，演示完毕" << endl;

    return 0;
}


