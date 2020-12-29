#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <string>
using namespace std;
//Input : 15/6+(31-6)*4 숫자마다 공백 삽입이 필요함. 15.2/6.1+(31.2-6.5)*4.8
//Output: 102.5000

string Expr;
string ModifiedExpr;
string postFix;
stack<float> st;

bool isOp(const char &ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')')
		return true;

	else return false;
}
int Getpriority(const char& ch)
{
	switch (ch)
	{
	case '(':	case ')':
		return 0;
	case '+':	case '-':
		return 1;
	case '*':	case '/':
		return 2;
	}
	return -1;
}
string toPostFix(const string &Expr)
{
	string res;
	stack<char> opstack;
	int i = 0;
	while (i < Expr.size())
	{
		char cur_ch = Expr[i];
		if (cur_ch == ' ')
		{
			//res.push_back(cur_ch);
			i++;
			continue;
		}
		if (!isOp(Expr[i]))//피연산자인경우
		{
			string str;
			while (i < Expr.size() && Expr[i] != ' ')
			{
				str.push_back(Expr[i]);
				i++;
			}
			res.append(str);
			res.push_back(' ');
		}
		else if (cur_ch == '(')
		{
			opstack.push(cur_ch);
		}
		else if (cur_ch == ')')
		{
			while (!opstack.empty())
			{
				char op = opstack.top();
				opstack.pop();
				if (op == '(')break;
				else
				{
					res.push_back(op);
					res.push_back(' ');
				}
				
			}
		}
		else
		{
			if (cur_ch == '+' || cur_ch == '-' || cur_ch == '*' || cur_ch == '/')//연산자인 경우
			{
				while (!opstack.empty())
				{
					char op = opstack.top();
					//현재 연산자보다 우선순위가 높거나 같으면 모두 출력한다.
					if (Getpriority(cur_ch) <= Getpriority(op))
					{
						res.push_back(op);//우선순위가 높은 연산자가 먼저 res에 적힌다.
						res.push_back(' ');
						opstack.pop();
					}
					else break;
				}

				opstack.push(Expr[i]);				
			}
			
		}
		i++;
	}
	while (!opstack.empty())
	{
		res.push_back(opstack.top());
		res.push_back(' ');
		opstack.pop();
	}
	return res;
}
string ModifiExpr(const string &str)
{
	string res;
	int i = 0;
	while (i < str.size())
	{
		if (isOp(str[i]))
		{
			res.push_back(' ');
			res.push_back(str[i]);
			if (i + 1 < str.size() && isOp(str[i+1]))
			{
				i++;continue;
			}
			else
			{
				res.push_back(' ');
			}
		}
		else
		{
			res.push_back(str[i]);
		}
		i++;
	}

	return res;
}
int main()
{
	cin >> Expr;
	ModifiedExpr = ModifiExpr(Expr);
	cout << ModifiedExpr<<endl;
	postFix = toPostFix(ModifiedExpr);
	cout << postFix<<endl;
}