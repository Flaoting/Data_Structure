/*1、系统进程统计（必做）（链表）
[问题描述]
　　设计一个程序，每秒统计一次当前系统的进程状况，并按照内存使用自多到少排序打印输出相关信息。对已经结束的进程，另外给出一个列表，并显示该进程的结束时间和持续时间。
[基本要求]
（1） 该题目要求使用两个链式线性表。一个链表存储当前活动进程，要求使用单向链表，并按照内存使用自多到少排序。
另外一个链表存储已结束进程，要求使用双向链表，按照持续时间自少到多排序。
（2） 每秒在窗口内更新一次当前系统进程情况，输出内容包括：进程名，持续时间，内存使用情况。
（3） 每秒在窗口内更新一次已结束进程情况，输出内容包括：进程名，持续时间，结束时间。
（4） 注意进程在这两个链表中的切换，一个进程既可被结束，也可以过一段时间后再被运行。
*/

#include "Process.h"
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cwchar>
#include <tchar.h>
/*定义数据结构*/

typedef struct SNode
{
	ProInfo data;
	struct SNode* next;
}SNode, * SList; 	//单链表结点

typedef struct DNode
{
	ProInfo data;
	struct DNode* next;
	struct DNode* pre;
}DNode, * DList; //双链表结点 The process that has ended

MSTime SubTime(const Time& a, const Time& b)
{
	int ans = 0;
	MSTime res;
	ans += (a.Second - b.Second);
	ans += (a.Minute - b.Minute) * 60;
	ans += (a.Hour - b.Hour) * 3600;
	ans += (a.Day - b.Day) * 24 * 3600;
	res.second = ans % 60;
	res.minute = ans / 60;
	return res;
}
/*返回 a - b 的值*/
vector<ProInfo> GetProcess()	
{
	vector<ProInfo> res;
	ProInfo *prolist;
	prolist = new ProInfo[1024];
	int pronum;
	//执行
	GetCurrentProcesses(prolist, pronum, 1024);
	for (int i = 0; i <= pronum - 1; i++)
	{
		res.push_back(prolist[i]);
		//PrintProInfo(prolist[i]);
	}
	return res;
}
//获取当前进程并返回一个vector<ProData>

class ProcessInRunning
{
private:
	SList L;		//链表头指针
	int length;		//链表长度
public:
	
	ProcessInRunning();
	~ProcessInRunning();
	SList GetLPtr();
	int GetLength();
	bool CreateSList(vector<ProInfo> res);	//通过vector初始化一个链表
	void DisplaySList();
	void InsertSort();
	void PtrCpy(const SList Ptr);
	void clear();
	void empty();
};
//正在进行的进程表

ProcessInRunning::ProcessInRunning()
{
	L = new SNode;		//注意 头结点申请了一个空间，但没有存放数据，第一个数据是从他的next开始的
	L->next = NULL;
	this->length = 0;
	L->data.ID = -9999;	//出现错误的话头结点的标准
}

ProcessInRunning::~ProcessInRunning()
{

}

SList ProcessInRunning::GetLPtr() 
{
	return this->L;
}

int ProcessInRunning::GetLength()
{
	return this->length;
}

bool ProcessInRunning::CreateSList(vector<ProInfo> res) 
{
	if (res.size() == 0)
	{
		cout << "数据获取异常，初始化失败" << endl;
		return false;
	}
	SNode* p = NULL, *pre = this->L;

	for (vector<ProInfo>::iterator iter = res.begin(); iter != res.end(); iter++)
	{
		p = new SNode;
		ProInfoCPY(p->data, *iter);
		pre->next = p;
		p->next = NULL;
		pre = p;
		this->length++;
	}
	/*for (int i = 0; i < 10; i++) 
	{
		p = new SNode;
		ProInfoCPY(p->data, res[i]);
		pre->next = p;
		p->next = NULL;
		pre = p;
		this->length++;
	}*/
	return true;
}

void ProcessInRunning::DisplaySList() 
{
	SNode* p = this->L->next;
	while (p != NULL) 
	{
		PrintProInfo(p->data);
		p = p->next;
	}
	return;
}

void ProcessInRunning::InsertSort()
{
	SList New;
	New = new SNode;
	New->next = NULL;
	SNode* p, * pre_p, * max_p, * max_pre;
	
	while (L->next != NULL)
	{
		pre_p = L;			//pre_p指向头结点(无数据)
		p = L->next;	//p指向第一个结点
		max_p = L->next;
		max_pre = L;
		while (p != NULL)	//找出最大值
		{

			if (max_p->data.Memory < p->data.Memory) 
			{
				max_p = p;
				max_pre = pre_p;
			}
			pre_p = p;
			p = p->next;
		}
		max_pre->next = max_p->next;
		max_p->next = New->next;
		New->next = max_p;
	}
	this->L->next = New->next;

	return;
}

void ProcessInRunning::clear() 
{
	SNode* p, * q = NULL;
	p = this->L->next;
	this->L->next=NULL;
	while (p != NULL) 
	{
		q = p;
		p = p->next;
		free(q);
	}
	return;
}

void ProcessInRunning::PtrCpy(const SList Ptr)
{
	if (Ptr == NULL)
	{
		return;
	}
	this->L->next = Ptr->next;
	return;
}

void ProcessInRunning::empty() 
{
	this->L->next = NULL;
	return;
}

class ProcessHaveEnded
{
private:
	DList L;
	int length;

public:
	ProcessHaveEnded();
	~ProcessHaveEnded();
	
	DList GetLPtr();
	int GetLength();
	
	void InsertSort();
	//按照进程时间，对双向链表进行插入排序

	void CreateDList(const SList& pre, const  SList& now);
	//通过上一秒的链表和这一秒的链表对比，找出结束的进程，加入链表

	void UpDateDList(const SList& now);
	//根据当前的进程，发现有没有结束的进程被重新激活，有的话就删除

	void DisplayDList();
	//打印链表

	void UpDateDList_Sec(const SList& now);

};
//已经结束的进程表

ProcessHaveEnded::ProcessHaveEnded()
{
	L = new DNode;
	L->next = NULL;
	this->length = 0;
}

ProcessHaveEnded::~ProcessHaveEnded()
{
}

DList ProcessHaveEnded::GetLPtr()
{
	return this->L;
}

int ProcessHaveEnded::GetLength()
{
	return this->length;
}

void ProcessHaveEnded::CreateDList(const SList &pre, const  SList &now)
{
	SNode* p1, * p2;
	bool flag;
	p1 = pre->next;
	while (p1 != NULL) 
	{
		flag = false;
		p2 = now->next;
		while (p2 != NULL)
		{
			if (p1->data.ID == p2->data.ID) 
			{
				//cout << "---" << p1->data.ID;
				flag = true;	//说明进程未结束
				break;
			}
			p2 = p2->next;
		}
		if (!flag)				//没有找到说明进程已经结束了
		{
			DNode *temp,*j;		//申请一个节点，插入到结束的进程链表中
			temp = new DNode;
			Time now_time;

			ProInfoCPY(temp->data, p1->data);
			GetSystime(now_time);

			temp->data.EndTime = now_time;
			temp->data.DuraTime = SubTime(temp->data.EndTime, temp->data.BeginTime);
			
			cout << temp->data.DuraTime.minute << "分" << temp->data.DuraTime.second <<"秒"<< endl;
			int t;
			cin >> t;
			j = this->L->next;
			if (j != NULL)
			{
				j->pre = temp;		//进行结点的插入
			}
			
			temp->next = j;
			L->next = temp;
			temp->pre = L;
			this->length++;
		}
		p1 = p1->next;
	}
	return;
}

void ProcessHaveEnded::UpDateDList(const SList& now) 
{
	DNode* p1,*pre,*nxt;
	SNode* q1;
	bool flag = false;
	p1 = this->L->next;

	while (p1 != NULL)
	{
		flag = false;
		q1 = now->next;
		while (q1 != NULL) 
		{
			if (q1->data.ID == p1->data.ID)		//如果这个进程存在，在ended列表中删除 
			{
				flag = true;
				nxt = p1->next;
				pre = p1->pre;

				pre->next = nxt;
				
				if (nxt != NULL) 
				{
					nxt->pre = pre;
				}
				this->length--;
				break;
			}
			q1 = q1->next;
		}
		pre = p1;
		p1 = p1->next;
		if (flag)
		{
			free(pre);
		}
	}
	return;
}

void ProcessHaveEnded::UpDateDList_Sec(const SList& now)
{
	DNode* p1, * pre, * nxt;
	SNode* q1;
	bool flag = false;
	p1 = this->L->next;

	while (p1 != NULL)
	{
		flag = false;
		q1 = now->next;
		while (q1 != NULL)
		{
			if (_tcscmp(q1->data.Name, p1->data.Name) == 0)		//如果这个进程存在，在ended列表中删除 
			{
				flag = true;
				nxt = p1->next;
				pre = p1->pre;

				pre->next = nxt;

				if (nxt != NULL)
				{
					nxt->pre = pre;
				}
				this->length--;
				break;
			}
			q1 = q1->next;
		}
		pre = p1;
		p1 = p1->next;
		if (flag)
		{
			free(pre);
		}
	}
	return;
}


void ProcessHaveEnded::InsertSort() 
{
	if (this->length <= 1)
	{
		return;
	}
	DList New;
	New = new DNode;
	New->next = NULL;
	DNode* p, * pre_p, * max_p, * max_pre;
	DNode* max_nxt;

	while (L->next != NULL)
	{
		pre_p = L;			//pre_p指向头结点(无数据)
		p = L->next;	//p指向第一个结点
		max_p = L->next;
		max_pre = L;
		while (p != NULL)	//找出最大值
		{
			if (max_p != NULL && p != NULL &&MSTimeCMP(max_p->data.DuraTime, p->data.DuraTime)<=0)
			{
				max_p = p;
				max_pre = pre_p;
			}			
			pre_p = p;
			p = p->next;
		}
		max_nxt = max_p->next;
		max_pre->next = max_nxt;
		if (max_nxt != NULL) 
		{
			max_nxt->pre = max_pre;
		}
		max_p->next = New->next;
		New->next = max_p;
		if (max_p->next != NULL)
		{
			max_p->next->pre = max_p;
		}
	}
	this->L->next = New->next;
	if (New->next != NULL)
	{
		New->next->pre = this->L;
	}
	return;
}

void ProcessHaveEnded::DisplayDList()
{
	DNode* p;
	p = this->L->next;
	cout << "%       " << this->length << endl;
	while (p != NULL) 
	{
		PrintProInfo(p->data);
		p = p->next;
	}
	return;
}

void print(int i)
{
	cout << "************第**" << i << "**次打印***********************" << endl;
	return;
}

void Conseal() 
{
	AdjustPurview();
	//初始化(这个待定是不是每次都要进行一次初始化)
	
	ProcessInRunning PIR_old,PIR_new;	//两个进程链表
	ProcessHaveEnded PHE;

	PIR_old.CreateSList(GetProcess());		//获得初始进程
	PIR_old.InsertSort();
	
	for (int i = 1; i <= 100; i++) 
	{
		Sleep(1000);		
		PIR_new.CreateSList(GetProcess());	//获得当前进程
		PIR_new.InsertSort();
		PHE.UpDateDList_Sec(PIR_new.GetLPtr());		//删除重启的进程
		PHE.CreateDList(PIR_old.GetLPtr(), PIR_new.GetLPtr());	//增加关闭的进程
		print(i);
		PHE.InsertSort();
		PHE.DisplayDList();
		
		PIR_old.clear();
		PIR_old.PtrCpy(PIR_new.GetLPtr());	//更新初始进程
		PIR_new.empty();
	}
	return;
}

int main()
{
	Conseal();
	return 0;
}


