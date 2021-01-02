/*
3、家谱管理系统（必做）（树）
[问题描述]
实现具有下列功能的家谱管理系统。
[基本要求]
（1）输入文件以存放最初家谱中各成员的信息，
成员的信息中均应包含以下内容：姓名、出生日期、婚否、地址、健在否、死亡日期（若其已死亡）。√
（2）实现数据的文件存储和读取。√
（3）以图形方式显示家谱。
（4）显示第n 代所有人的信息。√
（5）按照姓名查询，输出成员信息（包括其本人、父亲、孩子的信息）。√
（6）按照出生日期查询成员名单。√
（7）输入两人姓名，确定其关系。
（8）某成员添加孩子。
（9）删除某成员（若其还有后代，则一并删除）。
（10）修改某成员信息。
（11）要求建立至少40个成员的数据，以较为直观的方式显示结果，并提供文稿形式以便检查。
（12）界面要求：有合理的提示，每个功能可以设立菜单，根据提示，可以完成相关的功能要求。
（13）存储结构：根据系统功能要求自行设计，但是要求相关数据要存储在数据文件中。测试数据：要求使用1、全部合法数据；2、局部非法数据。进行程序测试，以保证程序的稳定。
*/

#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;


typedef struct PeopleData
{
	string name;
	bool AliveStatus;	//是否活着
	string DataOfBrith;
	string DataOfDeath;
	bool MaritalStatus;	//婚姻状况
	string Address;

}PeopleData;	//打包成一个人的信息

typedef struct People
{
	PeopleData data;
	int level;
	struct People* firstchild;	//第一个孩子
	struct People* nextBrother;	//左右兄弟
	struct People* leftBrother;	
	struct People* parent;		//祖先指针
}People, * Tree;

typedef struct Date
{
	int year;
	int month;
	int day;

	//运算符重载，所有的都是数值的比较，例如1984<1996
	bool operator <= (const Date a)const 
	{
		if (year != a.year) 
		{
			return year < a.year;
		}
		else
		{
			if (month != a.month)
			{
				return month < a.month;
			}
			else 
			{
				if (day != a.day)
				{
					return day < a.day;
				}
				else 
				{
					return true;	//相等也返回true
				}
			}
		}
		return false;
	}
	bool operator < (const Date a)const
	{
		if (year != a.year)
		{
			return year < a.year;
		}
		else
		{
			if (month != a.month)
			{
				return month < a.month;
			}
			else
			{
				if (day != a.day)
				{
					return day < a.day;
				}
				else
				{
					return false;	//相等也返回true
				}
			}
		}
		return false;
	}

}Date;


int StringToInt(string s) 
{
	int num = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (num == 0)
		{
			num = s[i] - '0';
			continue;
		}
		if (s[i] >= '0' || s[i] <= '9')
		{
			num *= 10;
			num += s[i] - '0';
		}
	}
	return num;
}

Date StringToDate(string &str)
{
	Date date;

	if (str == "")
	{
		date.day = 1;
		date.year = 1;
		date.month = 1;
		return date;
	}
	stringstream input(str);
	string temp = "1";
	vector<int> res;
	int t = 9;
	char pattern = '.';
	while (getline(input, temp, pattern))
	{
		t = StringToInt(temp);
		res.push_back(t);
	}
	date.year = res[0];
	date.month = res[1];
	date.day = res[2];
	return date;
}

void printDate(Date d)
{
	cout << d.year << "年" << d.month << "月" << d.day << "日";
	return;
}

vector<string> split_with(const string& str)
{
	stringstream input(str);
	string temp;
	vector<string> res;
	char pattern = ',';
	while (getline(input, temp, pattern))
	{
		res.push_back(temp);
	}
	return res;
}

string GetMaritalStatus(bool b) 
{
	if (b) 
	{
		return "已婚";
	}
	else 
	{
		return "未婚";
	}
}

void printPeopleInfo(People* peo) 
{
	if (peo == NULL)
	{
		cout << "Oh, you can't print a null's personal information." << endl;
		return;
	}

	cout << "姓    名 : " << peo->data.name << endl;
	cout << "婚姻状况 : " << GetMaritalStatus(peo->data.MaritalStatus) << endl;
	cout << "出生日期 : " << peo->data.DataOfBrith << endl;
	if (!peo->data.AliveStatus)
	{
		cout << "逝世日期 : " << peo->data.DataOfDeath << endl;
	}
	cout << endl;
	return;
}
//打印一个人的基本信息

void printRealtionInfo(People* peo)
{
	
	if (peo == NULL)
	{
		cout << "Oh, you can't print a null's relation information." << endl;
		return;
	}

	cout << "查询成功  即将打印信息..."<<endl;
	//_sleep(1); 
	cout << "-----------------------------------------------------" << endl;
	cout << "本人信息 : "<<endl;
	printPeopleInfo(peo);
	cout << "-----------------------------------------------------" << endl;
	cout << endl;


	cout << "-----------------------------------------------------" << endl;
	cout << "父亲信息 : ";
	if (peo->parent == NULL)
	{
		cout << peo->data.name << " 在家谱中没有其父亲的信息" << endl;
	}
	else 
	{
		cout << peo->data.name << " 的父亲是 " << peo->parent->data.name << endl;
		printPeopleInfo(peo->parent);
	}
	cout << "-----------------------------------------------------" << endl;

	cout << endl;

	cout << "-----------------------------------------------------" << endl;
	cout << "孩子信息 : ";
	People* p = peo->firstchild;
	vector<string> res_name;
	queue<Tree>Q;
	if (p == NULL)
	{
		cout << peo->data.name << " 在家谱中没有其孩子的信息" << endl;
	}
	else 
	{
		while (p != NULL)
		{
			Q.push(p);
			res_name.push_back(p->data.name);
			p = p->nextBrother;
		}
		cout << peo->data.name << " 共有 " << res_name.size() << "个孩子, 分别是 ";
		for (vector<string>::iterator iter = res_name.begin(); iter != res_name.end(); iter++)
		{
			cout << *iter << " ";
		}
		cout << endl<<endl;
		while (!Q.empty())
		{
			p = Q.front();
			Q.pop();
			printPeopleInfo(p);
		}
	}
	cout << "-----------------------------------------------------" << endl;
	return;
}
//打印一个人的本人、父亲、孩子信息


class Genealogy
{
private:
	Tree AncePtr;			//祖先指针，这个结点不存内容
	int personNum;			//这个家谱有多少人
	int levelNum;			//这个家谱有几代人
	
public:
	Genealogy();
	~Genealogy();
	bool JudgeStatus(string s);
	//判断一个状态字符串的是与否
	void BuildTreeFromFile();
	//从文件读取数据建立家谱
	bool InsertNewMan(vector<string> &res);
	
	void showGeneratinN(int n);

	void QueryByName(string name);

	void QueryByBirthAndShowList(string start, string end);
};

Genealogy::Genealogy()
{
	this->levelNum = 0;
	this->personNum = 0;
	this->AncePtr = NULL;
	this->AncePtr = new People;
	this->AncePtr->firstchild = NULL;
	this->AncePtr->leftBrother = NULL;
	this->AncePtr->level = 0;
	this->AncePtr->nextBrother = NULL;
	this->AncePtr->parent = NULL;
}

Genealogy::~Genealogy()
{

}

void Genealogy::BuildTreeFromFile() 
{
	fstream file("3.csv", ios::in);
	if (!file)
	{
		cout << "Sorry, source file can't be opened! " << endl;
		exit(0);
	}
	string line = "";
	vector<string> res;
	while (!file.eof()) 
	{
		file >> line;
		res = split_with(line);
		
		this->InsertNewMan(res);
	}
}

bool Genealogy::JudgeStatus(string s)
{
	string str1 = "有", str2 = "是", str3 = "已",str4 = "健在";
	if (s.find(str1) != string::npos || s.find(str2) != string::npos || s.find(str3) != string::npos)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool Genealogy::InsertNewMan(vector<string> &res)
{
	if (res.size() != 7)	//数据格式不对的话，防止错误的访问
	{
		for (vector<string> ::iterator iter = res.begin(); iter != res.end(); iter++)
		{
			cout << *iter << " ";
		}
		cout << endl;
		cout << res.size() << endl;
		cout << "FUCK" << endl;
		return false;
	}


	if (this->AncePtr== NULL)
	{
		cout << "You can't insert anything to NULL Tree" << endl;
		return false;
	}

	int count = res[6].length();

	string pos = res[6];
	People *peo = new People;

	peo->data.name = res[0];
	peo->data.AliveStatus = JudgeStatus(res[1]);
	peo->data.DataOfBrith = res[2];
	peo->data.DataOfDeath = res[3];
	peo->data.MaritalStatus = JudgeStatus(res[4]);
	peo->data.Address = res[6];

	peo->firstchild = NULL;
	peo->nextBrother = NULL;
	peo->level = 0;
	peo->leftBrother = NULL;
	peo->parent = NULL;

	Tree p = this->AncePtr;	//指向祖先指针
	
	if (count == 1 && p->firstchild == NULL)	//特判插入祖先的情况
	{
		this->AncePtr->firstchild = peo;
		peo->level = 1;
		return true;
	}

	int i = 0;
	char temp;
	
	while (count > 0 && p != NULL)
	{
		temp = pos[i];
		if (temp == '0')
		{
			p = p->nextBrother;
		}
		else if (temp == '1')
		{
			p = p->firstchild;
		}
		else
		{
			cout << "Your pos is invalid, the string pos is " << pos << endl;
			return false;
		}
		count--;
		i++;
	}

	if (p == NULL)
	{
		cout << "Insert position is invalid, the string pos is " << pos << " and the count is " << count << endl;
		return false;
	}

	//找到了爸爸

	People *q = p->firstchild;
	
	peo->level = p->level + 1;  //层次加一
	peo->parent = p;			//标记父亲
	if (peo->level > this->levelNum) 
	{
		this->levelNum++;
	}
	if (q == NULL)
	{
		p->firstchild = peo;
	}
	else
	{
		while (q->nextBrother != NULL)
		{
			q = q->nextBrother;
		}
		q->nextBrother = peo;
		peo->leftBrother = q;
	}

#ifdef myDebug
		static int cnt = 0;
		cnt++;
		cout << cnt << "  " << peo->data.name << "  的爸爸是 " << p->data.name << endl;
#endif // myDebug
	
	this->personNum++;
	return true;
}

void Genealogy::showGeneratinN(int n)
{

	if (n<0 || n>this->levelNum)
	{
		cout << "Error, The generation of " << n << " is not existed !!" << endl;
		return;
	}

	People* p = this->AncePtr;
	queue<Tree> Q;
	Q.push(p);

	while (!Q.empty()) 
	{
		p = Q.front();
		if (p->level == n)	//找到了第n层 
		{
			break;
		}
		Q.pop();
		p = p->firstchild;
		//cout << p->data.name << endl;
		while (p != NULL) 
		{
			//cout << " hhhh " << p->data.name << " " << p->level << endl;
			Q.push(p);
			p = p->nextBrother;
		}
	}
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		printPeopleInfo(p);
	}
}

void Genealogy::QueryByName(string name) 
{

	bool flag = false;
	People* p = this->AncePtr;
	queue<Tree> Q;
	Q.push(p);

	while (!Q.empty())
	{
		p = Q.front();
		
		if (p->data.name == name) 
		{
			flag = true;
			printRealtionInfo(p);
			break;
		}

		Q.pop();
		p = p->firstchild;
		//cout << p->data.name << endl;
		while (p != NULL)
		{
			//cout << " hhhh " << p->data.name << " " << p->level << endl;
			Q.push(p);
			p = p->nextBrother;
		}
	}
	if (!flag)
	{
		cout << "Sorry, we can't find this people in the genealogy, please make sure your spell" << endl;
	}
	return;
}

void Genealogy::QueryByBirthAndShowList(string s, string e)
{
	Date start, end, now;
	start = StringToDate(s);
	end = StringToDate(e);
	People* p = this->AncePtr->firstchild;
	queue<Tree> Q,ans;
	Q.push(p);
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		now = StringToDate(p->data.DataOfBrith);
		
		if (start <= now && now <= end)		//只重载了<=,所以看起来比较奇怪
		{
			ans.push(p);	//找到的话，就记录答案
		}
		p = p->firstchild;
		while (p != NULL)
		{
			Q.push(p);
			p = p->nextBrother;
		}
	}
	if (ans.size() == 0) 
	{
		cout << "没有找到出生日期在 ";
		printDate(start);
		cout << " 到";
		printDate(end);
		cout << "之间出生的人员" << endl;
	}
	else 
	{
		cout << "查询成功  即将打印信息..." << endl;
		//_sleep(1); 
		cout << "-----------------------------------------------------" << endl;

		cout << "出生日期在 ";
		printDate(start);
		cout << " 到";
		printDate(end);
		cout << "之间出生的人员共有 " << ans.size()<<"名"<<endl;
		cout << "详细个人信息如下 : " << endl << endl;
		while (!ans.empty())
		{
			p = ans.front();
			printPeopleInfo(p); 
			ans.pop();
		}
		cout << "-----------------------------------------------------" << endl;
	}
}

int main() 
{
	Genealogy g;
	g.BuildTreeFromFile();
	g.QueryByBirthAndShowList("1870.3.1", "1991.10.23");
	return 0;
}



