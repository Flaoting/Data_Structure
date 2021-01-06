#include<stdio.h>
#include <stack>
#include<stdlib.h>
#include <iostream>
#include <string>
using namespace std;
//定义算符之间优先关系的二维数组 
char prior[7][7] = { {'>','>','<','<','<','>','>'},
					{'>','>','<','<','<','>','>'},
					{'>','>','>','>','<','>','>'},
					{'>','>','>','>','<','>','>'},
					{'<','<','<','<','<','=','!'},
					{'>','>','>','>','!','>','>'},
					{'<','<','<','<','<','!','='} };

//确定输入的字符如果是操作符的话判断在二维数组中的下标 若是数字的话就另外与操作符区分开 便于在输入表达式时是入哪个栈 
int Index(char c) {
	switch (c) {
	case '+': return 0;
	case '-': return 1;
	case '*': return 2;
	case '/': return 3;
	case '(': return 4;
	case ')': return 5;
	case '#': return 6;
	default:  return 7;
	}
}

//判断优先级,返回大小 < > = !
char Priority(char a, char b) {
	int x, y;
	x = Index(a);
	y = Index(b);
	if (x != 7 && y != 7)
		return prior[x][y];
	else
		return '!';
}
//简单表达式求值
int Reckon(int a, char theta, int b)
{
	switch (theta)
	{
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a * b;
	case '/':return a / b;
	}
}
//判断是字符是否是数字
bool isdigit(char ch)
{
	if (ch >= '0' && ch <= '9') return true;
	return false;
}
//算术表达式求值

void showOPTRStack(stack<char> S) 
{
	stack<char>ss;
	while (!S.empty())
	{
		ss.push(S.top());
		S.pop();
	}
	cout << "OPTR栈当前情况 : ";
	while (!ss.empty())
	{
		cout << ss.top()<<" ";
		ss.pop();
	}
	cout << endl;
	return;

}

void showOPNDStack(stack<int> S)
{
	stack<int>ss;
	while (!S.empty())
	{
		ss.push(S.top());
		S.pop();
	}
	cout << "OPND栈当前情况 : ";
	while (!ss.empty())
	{
		cout << ss.top()<<" ";
		ss.pop();
	}
	cout << endl;
	return;
}

bool judge(string s)
{
	if (Index(s[0])!=4&&(s[0]<'0'||s[0])>'9')
	{
		cout << "表达式格式错误，第一个字符不可以是" << s[0] << endl;
		return false;
	}
	
	if (s.length() <= 2) 
	{
		cout << "运算式太短不合法" << endl;
		return false;
	}

	bool flag = false;
	int cnt_jing = 0;
	for (int i = 0; i < s.length(); i++) 
	{
		if (s[i] >= '0' && s[i] <= '9') 
		{
			
			continue;
		}
		else if (Index(s[i]) < 7)
		{
			if (i < s.length() - 1)
			{
				int k = Index(s[i + 1]);
				if (k != 4 && k != 5 && k != 6&&s[i+1]<'0'&&s[i+1]>'9') 
				{
					cout << "非法的运算符连续" << s[i] << s[i + 1] << "不能连续" << endl;
					return false;
				}
			}
			if (Index(s[i]) == 6) 
			{
				cnt_jing++;
			}
			flag = true;
			continue;
		}
		else 
		{
			cout << "符号 " << s[i] << " 不在规范码范围" << endl;
			return false;
		}
	}
	if (!flag)
	{
		cout << "无运算符，不合法" << endl;
		return false;
	}
	if (cnt_jing > 1)
	{
		cout << "#太多，不合法" << endl;
		return false;
	}
	else if (cnt_jing == 0) 
	{
		cout << "无#,不合法" << endl;
	}
	return true;
}

void GetExpressionValue()
{
	stack<char>OPTR;
	stack<int>OPND;
	OPTR.push('#');//将结束符置于操作符的底端  
	string str;
	cout << "请输入算术表达式:\n";
	cin >> str;
	if (!judge(str)) 
	{
		cout << "运算终止" << endl;
		return;
	}
	int j = 0;
	while (str[j] != '#' || OPTR.top() != '#') {//当*c=='#'&&栈顶字符=='#'的时候
		if (isdigit(str[j])) 
		{					//如果是数字的话将其转化为数字 然后入操作数栈 
			int data[10];
			int i = 0, num = 0;	//i是用于将字符串中的字符存入data数组 num是一个中间数 用于将字符串中的数字转化为整数然后入栈		
			while (isdigit(str[j]))
			{
				data[i] = str[j] - '0';
				i++;
				j++;
			}
			for (int j = 0; j < i; j++) 
			{
				num = num * 10 + data[j];
			}
			OPND.push(num);
			showOPNDStack(OPND);
		}
		else
		{
			int a, b;					//如果是字符的话将其入操作符栈
			char  theta;	//a b theta是用来返回操作数栈和操作符栈里的元素的
			switch (Priority(OPTR.top(), str[j])) {//比较即将入栈的字符与栈顶 操作符的优先级关系 
			case '<':
				OPTR.push(str[j]);
				showOPTRStack(OPTR);
				j++;
				break;
			case '>':
				b = OPND.top();
				OPND.pop();
				showOPNDStack(OPND);
				a = OPND.top();
				OPND.pop();
				showOPNDStack(OPND);
				theta = OPTR.top();
				OPTR.pop();
				showOPTRStack(OPTR);
				OPND.push(Reckon(a, theta, b));
				showOPNDStack(OPND);
				break;//将结果入栈 
			case '=':
				OPTR.pop();
				showOPTRStack(OPTR);
				j++;
				break;//说明括号相遇 删除栈内括号即可 
			default:break;
			}
		}
	}
	int result = OPND.top();
	showOPNDStack(OPND);
	cout << "结果是 " << result << endl;
}

int main() 
{
	GetExpressionValue();
}