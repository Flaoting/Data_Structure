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
（7）输入两人姓名，确定其关系。√
（8）某成员添加孩子。√
（9）删除某成员（若其还有后代，则一并删除）。√
（10）修改某成员信息。√
（11）要求建立至少40个成员的数据，以较为直观的方式显示结果，并提供文稿形式以便检查。
（12）界面要求：有合理的提示，每个功能可以设立菜单，根据提示，可以完成相关的功能要求。
（13）存储结构：根据系统功能要求自行设计，但是要求相关数据要存储在数据文件中。
测试数据：要求使用1、全部合法数据；2、局部非法数据。进行程序测试，以保证程序的稳定。
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
	string Relationship_identification_number;	//与祖先关系识别码,表明了他的父亲是谁

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
	cout << "家庭住址 : " << peo->data.Address << endl;
	cout << "关系码   : " << peo->data.Relationship_identification_number << endl;
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

void JustDisplayName(People* p)
{
	cout << p->data.name << " ";
}


class Genealogy
{
private:
	Tree AncePtr;			//祖先指针，这个结点不存内容
	int personNum;			//这个家谱有多少人
	int levelNum;			//这个家谱有几代人

public:
	Genealogy();
	~Genealogy();

	int returnLevel()
	{
		return this->levelNum;
	}
	bool JudgeStatus(string s);
	//判断一个状态字符串的是与否

	vector<string> GetAPersonFromConseal();
	//从屏幕获取一个人的信息,返回一个长度为6的vector

	People* GetPtrByName(string name);
	//通过姓名获得成员的指针

	void BuildTreeFromFile();
	//从文件读取数据建立家谱

	bool InsertNewMan(vector<string>& res);

	void showGeneratinN(int n);

	void QueryByName(string name);

	void QueryByBirthAndShowList(string start, string end);

	bool JudgeRelationship(string name1, string name2);
	//判断两个人的关系

	bool AddChild(string name);
	//添加某个成员的孩子,name是父亲的名字

	bool DeleteMembers(string name);
	//删除某成员及其孩子

	void ChangeMemberInfo(string name);
	//改变某成员的信息

	void IndentDisplay();
	//缩进打印家谱

	void UpdateFile();
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
		cout << "ERROR" << endl;
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
	peo->data.Address = res[5];
	peo->data.Relationship_identification_number = res[6];

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

People* Genealogy::GetPtrByName(string name) 
{
	People* p = this->AncePtr;
	queue<Tree>	Q;
	Q.push(p);

	while (!Q.empty()) 
	{
		p = Q.front();
		Q.pop();
		if (p->data.name == name)
		{
			return p;
		}
		else 
		{
			p = p->firstchild;
			while (p != NULL)
			{
				Q.push(p);
				p = p->nextBrother;
			}
		}
	}
	return NULL;
}

bool Genealogy::JudgeRelationship(string name1, string name2)
{
	People* p1 = NULL, * p2 = NULL, *pre = NULL;
	p1 = GetPtrByName(name1);
	p2 = GetPtrByName(name2);

	if (p1 == NULL || p2 == NULL)
	{
		if (p1 == NULL)
		{
			cout << "姓名为 " << name1 << " 的成员未在家谱中，请检查拼写是否正确。" << endl;
		}
		if (p2 == NULL)
		{
			cout << "姓名为 " << name2 << " 的成员未在家谱中，请检查拼写是否正确。" << endl;
		}
		return false;
	}
	else if (p1 == p2)
	{
		cout << "查询关系 " << name1 << " 与 " << name2 << " 为同一个人 " << endl;
		return true;
	}
	stack<Tree> S1, S2;
	queue<Tree> Q;
	S1.push(p1);
	S2.push(p2);
	
	while (p1->parent != NULL) 
	{
		p1 = p1->parent;
		S1.push(p1);
	}
	
	while (p2->parent != NULL)
	{
		p2 = p2->parent;
		S2.push(p2);
	}
	
	p1 = S1.top();
	p2 = S2.top();

	pre = this->AncePtr;

	while (p1 == p2 && !S1.empty() && !S2.empty() ) 
	{
		pre = p1;
		p1 = S1.top();
		p2 = S2.top();
		S1.pop();
		S2.pop();
	}

	Q.push(pre);

	if (S1.empty() || S2.empty())
	{
		Q.pop();
		p1 = GetPtrByName(name1);
		p2 = GetPtrByName(name2);
		if (S1.empty())
		{
			cout << name2 << " 是 " << name1 << " 的直系子孙" << endl<<endl;
			cout << name1;
			Q.push(p1);
			while (!S2.empty())
			{
				p2 = S2.top();
				Q.push(p2);
				S2.pop();
				cout << " --- " << p2->data.name;
			}
			cout << endl;
		}
		else 
		{
			cout << name1 << " 是 " << name2 << " 的直系子孙" << endl << endl;
			cout << name2;
			Q.push(p2);
			while (!S1.empty())
			{
				p1 = S1.top();
				Q.push(p1);
				S1.pop();
				cout << " --- " << p1->data.name;
			}
			cout << endl;
		}
		
	}

	else 
	{

		cout << pre->data.name << "--";

		while (!S1.empty())
		{
			p1 = S1.top();
			Q.push(p1);
			S1.pop();
			cout << " --- " << p1->data.name;
		}
		cout << endl;
		cout << "   |   " << endl;
		cout << "   |   " << endl;
		cout << "   ---";
		while (!S2.empty())
		{
			p2 = S2.top();
			Q.push(p2);
			S2.pop();
			cout << " --- " << p2->data.name;
		}
		cout << endl;
	}
	cout << endl;
	cout << "查询成功  即将打印信息..." << endl;
	//_sleep(1); 
	cout << "-----------------------------------------------------" << endl;

	cout << "所有涉及成员的详细信息如下" << endl;

	while (!Q.empty())
	{
		p1 = Q.front();
		Q.pop();
		printPeopleInfo(p1);
	}
	return true;
}

bool Genealogy::AddChild(string name)
{
	/*实现方法:查找父亲姓名，构造01串，构造孩子的数据包*/

	People* p, *q, *k;
	string relation_number;
	vector <string> res;
	p = GetPtrByName(name);
	if (p == NULL)
	{
		cout << "家谱中无查无此人,请检查拼写" << endl;
		return false;
	}
	q = p->firstchild;
	k = p->parent;
	if (q != NULL)	//有孩子直接定位
	{
		relation_number = q->data.Relationship_identification_number;
	}
	else	//无孩子就通过爷爷
	{
		relation_number = p->data.Relationship_identification_number;
		k = k->firstchild;
		while (k != NULL)
		{
			relation_number = relation_number + "0";
		}
	}

	cout << "注意 即将在家谱中以 " << name << " 为父亲插入成员插入成员" << endl;
	cout << "-----------------------------------------------------" << endl;
	res = GetAPersonFromConseal();
	res.push_back(relation_number);

	
	if (!this->InsertNewMan(res)) 
	{
		cout <<endl<< "插入失败，请检查" << endl;
		return false;
	}
	else 
	{
		cout << endl << "插入成功!!!" << endl;
		return true;
	}
}

vector<string> Genealogy::GetAPersonFromConseal()
{
	vector<string> res;
	string temp;
	bool flag = false;
	cout << "下面开始输入个人信息..." << endl;

	cout << "姓    名 : ";
	cin >> temp;
	res.push_back(temp);

	cout << "是否健在 : ";
	cin >> temp;
	res.push_back(temp);

	flag = this->JudgeStatus(temp);

	cout << "出生日期 : ";
	cin >> temp;
	res.push_back(temp);

	if (!flag) 
	{
		cout << "逝世日期 : ";
		cin >> temp;
		res.push_back(temp);
	}
	else 
	{
		temp = "";
		res.push_back(temp);
	}
	
	cout << "婚姻状况 : ";
	cin >> temp;
	res.push_back(temp);
	
	cout << "住    址 : ";
	cin >> temp;
	res.push_back(temp);

	return res;
}

bool Genealogy::DeleteMembers(string name) 
{
	/*逐出家门*/
	People* p , *q ,*k;
	q = NULL;
	k = NULL;
	p = GetPtrByName(name);
	if (p == NULL)
	{
		cout << "家谱中无查无此人,请检查拼写" << endl;
		return false;
	}
	q = p->parent->firstchild;
	//指向删除人的大哥(或者自己)

	if (p == q) //自己就是大哥的话
	{
		p->parent->firstchild = p->nextBrother;
		//自己是大哥，二哥变大哥
	}
	else 
	{
		//自己不是大哥，找到自己的上一个哥哥

		while (q != NULL)
		{
			if (q->nextBrother == p)
			{
				break;
			}
			q = q->nextBrother;
		}
		//q是上一个哥哥
		if (q != NULL) 
		{
			q->nextBrother = p->nextBrother;
			if (p->nextBrother != NULL)
			{
				p->nextBrother->leftBrother = q;
			}
		}
	}
	
	queue<Tree>Q,L;
	Q.push(p);
	int cnt = 0;
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		q = p->firstchild;
		while (q != NULL) 
		{
			Q.push(q);
			q = q->nextBrother;
		}
		L.push(p);
		cnt++;
	}
	cout << "即将删除 " << cnt << " 位成员 ....." << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "删除人员详细信息如下" << endl << endl;
	while (!L.empty())
	{
		p = L.front();
		L.pop();
		printPeopleInfo(p);
		free(p);
	}
	return true;
}

void Genealogy::ChangeMemberInfo(string name) 
{
	People* peo = GetPtrByName(name);
	vector<string> res;
	if (peo == NULL)
	{
		cout << "家谱中无查无此人,请检查拼写" << endl;
		return;
	}

	cout << "注意 即将修改以下成员的个人信息 " << endl;
	cout << "-----------------------------------------------------" << endl;
	printPeopleInfo(peo);

	cout << "-----------------------------------------------------" << endl;
	
	cout << "请重新输入的" << name << "个人信息" << endl;
	res = GetAPersonFromConseal();
	
	while(res.size() < 6) 
	{
		cout << "信息输入有误，输入信息为";
		for (vector<string>::iterator iter = res.begin(); iter != res.end(); iter++) 
		{
			cout << *iter << " ";
		}
		cout << endl;
		cout << "请重新输入的" << name << "个人信息" << endl;
		res = GetAPersonFromConseal();
	}
	
	peo->data.name = res[0];
	peo->data.AliveStatus = JudgeStatus(res[1]);
	peo->data.DataOfBrith = res[2];
	peo->data.DataOfDeath = res[3];
	peo->data.MaritalStatus = JudgeStatus(res[4]);
	peo->data.Address = res[5];

	cout << "信息修改成功!!" << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "当前个人信息为" << endl;
	printPeopleInfo(peo);
	cout << "-----------------------------------------------------" << endl;
	return;
}

void r_display(Tree peo, int gap)
{
	if (peo == NULL)
	{
		return;
	}
	for (int i = 0; i < gap; i++)
	{
		cout << "-";
		if (i % 4 == 0) 
		{
			cout << "*";
		}
	}
	JustDisplayName(peo);
	cout << endl;
	Tree child = peo->firstchild;
	r_display(child, gap + 6);

	Tree brother = peo->nextBrother;
	r_display(brother, gap);
}
//递归打印树

void Genealogy::IndentDisplay()
{
	if (this->AncePtr == NULL)
	{
		cout << "null" << endl;
	}
	else
	{
		r_display(this->AncePtr, 0);
	}
	return;
}

void menu()
{
	cout << "1.显示第n 代所有人的信息" << endl;
	cout << "2.按照姓名查询，输出成员信息（包括其本人、父亲、孩子的信息）" << endl;
	cout << "3.按照出生日期查询成员名单" << endl;
	cout << "4.输入两人姓名，确定其关系" << endl;
	cout << "5.某成员添加孩子" << endl;
	cout << "6.删除某成员（若其还有后代，则一并删除）" << endl;
	cout << "7.修改某成员信息" << endl;
	cout << "8.打印家谱" << endl;
	cout << "9.结束进程" << endl;
	return;
}

void Conseal() 
{
	Genealogy g;
	g.BuildTreeFromFile();

	cout << "--------------欢--迎--使--用--家--谱--系--统---------------" << endl;
	string s,oo;
	int k,temp;
	while (1)
	{
		cout << endl << endl;
		menu();
		cout << endl;
		cout << "请选择操作编号:";
		cin >> k;

		switch (k)
		{
			case 1:
			{
				cout << "当前最大代数为 : " << g.returnLevel() << endl;
				cout << "请输入要选择第几代人:";
				cin >> temp;
				if (temp > g.returnLevel())
				{
					cout << "输 入 超 出 范 围 ！" << endl;
					break;
				}
				g.showGeneratinN(temp);
				break;
			}
			case 2: 
			{
				cout << "请输入要查询的姓名 : " << endl;
				cin >> s;
				g.QueryByName(s);
				break;
			}
			case 3:
			{
				cout << "日期格式为(xxxx.xx.xx)" << endl;
				cout << "请输入日期一:";
				cin >> s;
				cout << endl;
				cout << "请输入日期二:";
				cin >> oo;
				g.QueryByBirthAndShowList(s, oo);
				break;
			}
			case 4:
			{
				cout << "请输入姓名一 : ";
				cin >> s;
				cout << endl<< "请输入姓名二 : ";
				cin >> oo;
				g.JudgeRelationship(s, oo);
				break;
			}
			case 5: 
			{
				cout << "请输入姓名 : ";
				cin >> s;
				g.AddChild(s);
				break;
			}
			case 6: 
			{
				cout << "请输入姓名 : ";
				cin >> s;
				g.DeleteMembers(s);
				break;
			}
			case 7:
			{
				cout << "请输入姓名 : ";
				cin >> s;
				g.ChangeMemberInfo(s);
				break;
			}
			case 8: 
			{
				g.IndentDisplay();
				break;
			}
			case 9: 
			{
				exit(0);
			}
			default:
				cout << "输入无效" << endl;
				break;
		}

	}
	return;
}

int main() 
{
	
	/*g.DeleteMembers("王浩");
	printRealtionInfo(g.GetPtrByName("王景逸"));

	g.ChangeMemberInfo("王景逸");
	*/
	//g.IndentDisplay();
	Conseal();
	return 0;
}

