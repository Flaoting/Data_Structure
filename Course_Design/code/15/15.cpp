#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
int n, m;
string p[105]; //规则
string r[105]; //名称
string q[105]; //查询

vector< vector<string> > rule;

void read_file()
{
    fstream file("15.txt",ios::in);
    file>> n >> m;
    for(int i = 1; i <= n; i++)
    {
        file >> p[i] >> r[i];
    }
    for(int i = 1; i <= m; i++)
    {
        file >> q[i];
    }
    file.close();
    return;
}

void read()
{
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        cin >> p[i] >> r[i];
    }
    for(int i = 1; i <= m; i++)
    {
        cin >> q[i];
    }
    //file.close();
    return;
}

vector<string> split(const string &str)
{
    stringstream input(str);
    string temp;
    vector<string> res;
    char pattern = '/';
    while(getline(input,temp,pattern))
    {
        if(temp != "")
        {
            res.push_back(temp);
        }
    }
    return res;
}

bool basic_rule(string URL)
{
    for(int i = 0; i < URL.length(); i++)
    {
        if(URL[i] == '.' || URL[i] == '-' || URL[i] == '_' || URL[i] == '/' || (URL[i] >= '0' && URL[i]<='9') || (URL[i] >= 'A' && URL[i] <= 'Z')||(URL[i] >= 'a' && URL[i]<='z'))
        {
            continue;
        }
        return false;
    }
    for(int i = 1; i < URL.length(); i++)
    {
        if(URL[i] =='/' && URL[i-1] =='/')
        {
            return false;
        }
    }
    return true;
}

void init_rule()
{
    vector <string> s;
    s.push_back("hhh");
    rule.push_back(s);
    for(int i = 1; i <= n; i++)
    {
        rule.push_back( split(p[i]) );
    }
    return;
}

bool isNumber(string num)
{
    for(int i = 0; i < num.length(); i++)
    {
        if(num[i] < '0' || num[i] > '9')
        {
            return false;
        }
    }
    return true;
}

void print(vector<string> &s)
{
    string it;
    for(vector<string>::iterator iter = s.begin(); iter != s.end(); iter++)
    {
        it = *iter;
        int t = 0;
        while(it[t] == '0' && isNumber(it) && it.length() - t  > 1)
        {
            t++;
        }
        if(t >= 1)
        {
            for(int i = t; i < it.length(); i++)
            {
                cout << it[i];
            }
            cout << " ";
        }
        else 
        {
            cout << it << " ";
        }
    }
    return;
}

bool check(int i, int j)    //第i条数据，匹配第j条规则
{
    if(!basic_rule(q[i]))
    {
        return false;
    }
    int length_1 = p[j].length() - 1;
    int length_2 = q[i].length() - 1;

    if(p[j][length_1] == '/' && q[i][length_2] != '/')
    {
        return false;
    }
    if((p[j][length_1] != '/' && q[i][length_2] == '/'))
    {
        return false;
    }

    vector<string> res = split(q[i]);
    vector<string>::iterator it_1, it_2;
    it_1 = rule[j].begin();
    it_2 = res.begin();
    vector<string> canshu;
    bool flag;
    while(it_1 != rule[j].end() && it_2 != res.end())
    {
        
        if(*it_1 == "<int>" && *it_2 != "")
        {
            if(!isNumber(*it_2))
            {
                return false;
            }
            canshu.push_back(*it_2);
        }
        else if(*it_1 == "<str>" && *it_2 != "")
        {
            canshu.push_back(*it_2);
        }
        else if(*it_1 == "<path>" && *it_2 != "")
        {
            flag = true; //含有path的
            break;
        }
        else if(*it_1 != *it_2)
        {
            return false;
        }
        it_1++;
        it_2++;
    }
    if((it_1 != rule[j].end() || it_2 != res.end()) && !flag)
    {
        return false;
    }
    
    if(!flag)
    {   
        cout << r[j] <<" ";
        print(canshu);
        cout << endl;
    }
    else 
    {
        cout << r[j] <<" ";
        print(canshu);
        int k = 1, z=0;

        for(vector<string> :: iterator it = rule[j].begin(); it != it_1; it++)
        {
            k++;
        }
        
        for(z = 0; z < q[i].length(); z++)
        {
            if(k == 0)
            {
                break;
            }
            if(q[i][z] == '/')
            {
                k--;
            }
        }

        for(; z < q[i].length(); z++)
        {
            cout << q[i][z] ;
        }

        cout <<endl;
    }
    
    return true;
}
int main()
{
    bool flag;
    read_file();
    init_rule();
    for(int i = 1; i <= m; i++)
    {
        flag = false;
        for(int j = 1; j <= n; j++)
        {
            if(check(i,j))
            {
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            cout << "404" <<endl;
        }
    }
    return 0;
}

