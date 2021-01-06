/*18、【2】编写“连连看”程序。(选做)（图）
[问题描述]
建立一个10*20的矩形方格图，其中有10种不同的图案，每种图案个数为偶数，填满矩形方格图。
[基本要求]
（1）随机产生原始数据
（2）输入两个位置，如果两者图案相同，并且用少于等于3的直线相连，可消除该两个图案。
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <Windows.h>
using namespace std;

typedef struct node
{
	int x, y, dir, arc;
}Node;

char locn[15] = { 'A','B','C','D','E','F','G','H','I','J','K' };
int cn_t[15];

char Map[15][25];
bool flag[15][25];

void Generate()
{
	int temp = 0, cnt = 0,cc = 0;
	for (int i = 1; i <= 10; i++) 
	{
		cn_t[i] = 0;
	}
	srand((unsigned int)time(NULL));

	for (int i = 1; i <= 10; i++) 
	{
		for (int j = 1; j <= 20; j++) 
		{
			temp = rand();
			temp %= 10;
			cnt++;
			if(cnt>190)
			{
				cc = 0;
				while (cn_t[temp + 1] % 2 == 0) 
				{
					if (cc == 10) 
					{
						break;
					}
					temp++;
					temp %= 10;
					cc++;
				}
			}
			Map[i][j] = locn[temp + 1];
			cn_t[temp + 1]++;
		}
	}
	for (int i = 1; i <= 10; i++) 
	{
		for (int j = 1; j <= 20; j++) 
		{
			flag[i][j] = true;
		}
	}
	return;
}

void showMap()
{
	cout << endl << endl;
	cout << setw(4) << " ";
	for (int i = 1; i <= 20; i++) 
	{
		cout << setw(4) << i;
	}
	cout << endl;
	cout << "       -----------------------------------------------------------------------------" << endl;
	for (int i = 1; i <= 10; i++) 
	{
		cout <<setw(4)<<i<<"|";
		for (int j = 1; j <= 20; j++)
		{
			if (flag[i][j])
			{
				cout <<setw(4)<< Map[i][j];
			}
			else 
			{
				cout << setw(4)<<" ";
			}
		}
		cout << endl<<endl;
	}
	return;
}

bool isConseal(int x1, int y1, int x2, int y2) 
{
	if (x1 != x2 && y1 != y2) 
	{
		return false;
	}
	if (x1 > x2) 
	{
		swap(x1, x2);
	}
	if (y1 > y2)
	{
		swap(y1, y2);
	}
	if (x1 == x2)
	{
		for (int i = y1 + 1; i <= y2 - 1; i++) 
		{
			if (flag[x1][i]) 
			{
				return false;
			}
		}
		return true;
	}
	else 
	{
		for (int i = x1 + 1; i <= x2 - 1; i++)
		{
			if (flag[i][y1])
			{
				return false;
			}
		}
		return true;
	}
}

bool idDouble(const int x1, const int y1, const int x2,const int y2) 
{
	flag[x1][y1] = false;
	flag[x2][y2] = false;
	
	int start_x = x2, end_x =x2, start_y = y2, end_y = y2;
	
	while (start_x > 0 && !flag[start_x - 1][y2]) 
	{
		start_x--;
	}
	while (end_x < 11 && !flag[end_x + 1][y2])
	{
		end_x++;
	}
	while (start_y > 0 && !flag[x2][start_y-1])
	{
		start_y--;
	}
	while (end_y < 21 && !flag[x2][end_y+1])
	{
		end_y++;
	}
	/*cout << start_x <<"  "<< end_x << endl;
	
	cout << start_y << "  " << end_y << endl; */

	int p = x1;

	while (!flag[p][y1] && p >= 0)
	{
		for (int i = start_x; i <= end_x; i++) 
		{
			if (isConseal(p, y1, i, y2)) 
			{
				return true;
			}
		}
		p--;
	}
	
	p = x1;
	while (!flag[p][y1] && p <= 11)
	{
		for (int i = start_x; i <= end_x; i++)
		{
			if (isConseal(p, y1, i, y2))
			{
				return true;
			}
		}
		p++;
	}

	p = y1;
	while (!flag[x1][p] && p >= 0)
	{
		for (int i = start_y; i <= end_y; i++)
		{
			if (isConseal(x1, p, x2, i))
			{
				return true;
			}
		}
		p--;
	}

	p = y1;
	
	while (!flag[x1][p] && p <= 11)
	{
		for (int i = start_y; i <= end_y; i++)
		{
			if (isConseal(x1, p, x2, i))
			{
				return true;
			}
		}
		p++;
	}


	flag[x1][y1] = true;
	flag[x2][y2] = true;
	return false;
}

bool Eliminate(int x1,int y1,int x2,int y2)
{
	if (x1 == x2 && y1 == y2) 
	{
		return false;
	}

	if (x1 < 0 || x1>10)
	{
		return false;
	}

	if (x2 < 0 || x2>10)
	{
		return false;
	}

	if (y1 < 0 || y1>20)
	{
		return false;
	}

	if (y2 < 0 || y2 > 20)
	{
		return false;
	}

	if (Map[x1][y1] != Map[x2][y2]) 
	{
		return false;
	}
	if (!flag[x1][y1] || !flag[x2][y2])
	{
		return false;
	}
	
	if (isConseal(x1, y1, x2, y2))
	{
		return true;
	}
	else if (idDouble(x1, y1, x2, y2))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool judegEnd() 
{
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 20; j++)
		{
			if (flag[i][j])
			{
				return false;
			}
		}
	}
	return true;
}


void Display() 
{
	int a, b, c, d;
	while (1)
	{
		if (judegEnd())
		{
			int cnt = 3;
			while (cnt--)
			{
				cout << "你真是太厉害啦，恭喜通关!!!!!!" << endl;
			}
			break;
		}

		for (a = 10; a >= 1; a--)
		{
			for (b = 20; b >= 1; b--)
			{
				for (c = 10; c >= 1; c--)
				{
					for (d = 20; d >= 1; d--)
					{
						if (Eliminate(a, b, c, d))
						{
							cout << "即将更新..." << endl;
							//Sleep(1000);
							flag[a][b] = false;
							flag[c][d] = false;
							showMap();
							cout << "消除成功 ！！！" << endl;
						}
					}
				}
			}
		}
	}
}

void menu()
{
	string s;
	cout << "-------------------------欢--迎--来--到--连--连--看-------------------" << endl;
	cout << "------预--防--未--成--年--人--过--度--游--戏--从--你--我--做--起------" << endl;
	cout << endl << endl << endl;
	cout << "------1.手动消除-----" << endl;
	cout << "------2.模拟演示-----" << endl;
	cin >> s;
	if (s == "1")
	{
		int x1, x2, y1, y2;
		while (1)
		{
			cin >> x1 >> y1 >> x2 >> y2;

			if (Eliminate(x1, y1, x2, y2))
			{
				flag[x1][y1] = false;
				flag[x2][y2] = false;
				showMap();
				cout << "消除成功 ！！！" << endl;
			}
			else
			{
				cout << "坐标 (" << x1 << "," << y1 << ")  ";
				cout << " (" << x2 << "," << y1 << ")  ";
				cout << "   消除失败 ！" << endl;
			}
			if (judegEnd()) 
			{
				int cnt = 3;
				while (cnt--)
				{
					cout << "你真是太厉害啦，恭喜通关!!!!!!" << endl;
				}
				break;
			}

		}
	}
	else if (s == "2") 
	{
		Display();
		cout << "演示完毕" << endl;
	}
	else 
	{
		cout << " 输入无效 " << endl;
	}
}

int main()
{
	Generate();
	menu();
	return 0;
}