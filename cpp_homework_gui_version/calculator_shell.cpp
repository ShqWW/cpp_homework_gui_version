#include "calculator_shell.h"
//initialization
#include<iostream>    //////////////debug           
using namespace std;//////////////debug


calculator_shell::calculator_shell()
{
	this->expression == "";
	this->Ans = "";
	fun_list = {
		{ "sqrt",&calculator_shell::cal_sqrt} ,
		{ "cos",&calculator_shell::cal_cos} ,
		{ "sin",&calculator_shell::cal_sin} ,
		{ "tan",&calculator_shell::cal_tan} ,
		{ "arcsin",&calculator_shell::cal_arcsin} ,
		{ "arccos",&calculator_shell::cal_arccos} ,
		{ "arctan",&calculator_shell::cal_arctan} ,
		{ "sinh",&calculator_shell::cal_sinh} ,
		{ "cosh",&calculator_shell::cal_cosh} ,
		{ "tanh",&calculator_shell::cal_tanh} ,
		{ "arcsinh",&calculator_shell::cal_arcsinh} ,
		{ "arccosh",&calculator_shell::cal_arccosh} ,
		{ "arctanh",&calculator_shell::cal_arctanh} ,
		{ "lg",&calculator_shell::cal_lg} ,
		{ "ln",&calculator_shell::cal_ln} ,
		{ "abs",&calculator_shell::cal_abs},
		{ "!",&calculator_shell::cal_factor},
		{ "%",&calculator_shell::cal_percen} };
	cal_list = {
		{ "+",&calculator_shell::cal_add} ,
		{ "-",&calculator_shell::cal_minus} ,
		{ "*",&calculator_shell::cal_plus} ,
		{ "/",&calculator_shell::cal_devi} ,
		{ "^",&calculator_shell::cal_pow} };
	symbol_prio = {
		{"!",0},
		{"sqrt",1} ,
		{"cos",1} ,
		{"sin",1} ,
		{"tan",1} ,
		{"arcsin",1} ,
		{"arccos",1} ,
		{"arctan",1} ,
		{"sinh",1} ,
		{"cosh",1} ,
		{"tanh",1} ,
		{"arcsinh",1} ,
		{"arccosh",1} ,
		{"arctanh",1} ,
		{"lg",1} ,
		{"ln",1} ,
		{"abs",1} ,
		{"^",2},
		{"*",3},
		{"/",3},
		{"%",3},
		{"+",4},
		{"-",4} };
	const_sym = {
		{"e",2.7182818284590452353602874714},
		{"pi",3.1415926535897932384626433833} ,
		{"ans",0}
	};

	//cout << (this->*fun_list["!"])(5.1-0.1) << endl;//use method
}
void calculator_shell::get_expression(string s)
{
	this->expression = s;
}
void calculator_shell::inver_expression()
{
	this->restart();
	string::iterator expr_index = expression.begin();
	string::iterator expr_index_end = expression.end();
	string num_adfun = "";
	string curr_symbol = "?";
	bool dot = 0;
	bool is_num = 0;
	while (expr_index != expr_index_end)
	{

		if (*expr_index >= '0' && *expr_index <= '9')
		{
			while (expr_index != expr_index_end &&
				((*expr_index >= '0' && *expr_index <= '9')
					|| *expr_index == '.'))
			{
				if (*expr_index == '.' && dot)
				{
					string e = "illegal input";
					throw e;
				}
				else if (*expr_index == '.')
					dot = 1;
				num_adfun.push_back(*expr_index);
				expr_index++;
			}
			dot = 0;
			expr_index--;
			is_num = 1;
			postfix_expression.push_back(num_adfun);
			num_adfun = "";
		}
		else if (*expr_index >= 'a' && *expr_index <= 'z')
		{
			while (expr_index != expr_index_end && *expr_index >= 'a' && *expr_index <= 'z')
			{
				num_adfun.push_back(*expr_index);
				expr_index++;
			}
			if (const_sym.find(num_adfun) != const_sym.end())
			{
				postfix_expression.push_back(num_adfun);
				num_adfun = "";
				is_num = 1;
				continue;
			}//////////ÕÒ pi e ºÍans
			if (fun_list.find(num_adfun) == fun_list.end())
			{
				cout << num_adfun << endl;
				string e = "illegal input";
				throw e;
			}
			expr_index--;
			while ((!symbol.empty()) && symbol.back() != "(" && symbol_prio[num_adfun] >= symbol_prio[symbol.back()])
			{
				postfix_expression.push_back(symbol.back());
				symbol.pop_back();
			}
			symbol.push_back(num_adfun);
			num_adfun = "";
			is_num = 0;
		}
		else if (*expr_index == '(')
		{
			symbol.push_back("(");
			is_num = 0;
		}
		else if (*expr_index == ')')
		{
			while (!symbol.empty() && symbol.back() != "(")
			{
				postfix_expression.push_back(symbol.back());
				symbol.pop_back();
			}
			if (symbol.empty())
			{
				string e = "parentheses unmatched";
				throw e;
			}
			symbol.pop_back();
		}
		else
		{
			curr_symbol[0] = *expr_index;
			if (symbol_prio.find(curr_symbol) == symbol_prio.end())
			{
				string e = "illegal input";
				throw e;
			}
			if ((!is_num) && (curr_symbol == "+" || curr_symbol == "-"))
			{
				postfix_expression.push_back("0");
				is_num = 0;
			}
			else
			{
				while ((!symbol.empty()) && symbol.back() != "(" && symbol_prio[curr_symbol] >= symbol_prio[symbol.back()])
				{
					postfix_expression.push_back(symbol.back());
					symbol.pop_back();
				}
			}
			symbol.push_back(curr_symbol);
			if (curr_symbol != "!" && curr_symbol != "%")
			{
				is_num = 0;
			}
		}
		expr_index++;
	}
	while (!symbol.empty())
	{
		if (symbol.back() == "(")
		{
			string e = "parentheses unmatched";
			throw e;
		}
		else
		{
			postfix_expression.push_back(symbol.back());
			symbol.pop_back();
		}
	}
	output_inver_expression();
}
string calculator_shell::cal_outcome()
{
	string s;
	long double num_curr;
	while (!postfix_expression.empty())
	{
		s = postfix_expression.front();
		postfix_expression.pop_front();
		if (s[0] >= '0' && s[0] <= '9')
		{
			stringstream str2num;
			str2num << s;
			str2num >> num_curr;
			number.push_back(num_curr);
		}
		else if (const_sym.find(s) != const_sym.end())
		{
			number.push_back(const_sym[s]);
		}
		else if (fun_list.find(s) != fun_list.end())
		{
			if (number.empty())
			{
				string e = "illegal input";
				throw e;
			}
			else
			{
				try
				{
					num_curr = (this->*fun_list[s])(number.back());
					number.pop_back();
					number.push_back(num_curr);
				}
				catch (string e)
				{
					throw(e);
				}
			}
		}
		else
		{
			if (number.empty())
			{
				string e = "illegal input";
				throw e;
			}
			else
			{
				num_curr = number.back();
				number.pop_back();
			}
			if (number.empty())
			{
				string e = "illegal input";
				throw e;
			}
			else
			{
				try
				{
					num_curr = (this->*cal_list[s])(number.back(), num_curr);
					number.pop_back();
					number.push_back(num_curr);
				}
				catch (string e)
				{
					throw(e);
				}
			}
		}
	}
	num_curr = number.back();
	number.pop_back();
	if (!number.empty())
	{
		string e = "illegal input";
		throw e;
	}
	else
	{
		ans = num_curr;
		const_sym["ans"] = ans;
		stringstream num2str;
		num2str << num_curr;
		num2str >> Ans;
		return Ans;
	}
}

void calculator_shell::output_inver_expression()
{
	int k = postfix_expression.size();
	for (int i = 0; i < k; i++)
	{
		cout << postfix_expression[i] << " ";
	}
	cout << endl;
}
//////////////debug


void calculator_shell::restart()
{
	string expression = "";
	while (!postfix_expression.empty())
		postfix_expression.pop_back();
	while (!symbol.empty())
		symbol.pop_back();
	while (!number.empty())
		number.pop_back();
}

long double calculator_shell::cal_add(long double x, long double y)
{
	return x + y;
}
long double calculator_shell::cal_minus(long double x, long double y)
{
	return x - y;
}
long double calculator_shell::cal_plus(long double x, long double y)
{
	return x * y;
}
long double calculator_shell::cal_devi(long double x, long double y)
{

	if (y == 0)
	{
		string e = "divisor shouldn't be zero";
		throw e;
	}
	else
		return x / y;
}
long double calculator_shell::cal_pow(long double x, long double y)
{
	return pow(x, y);
}
long double calculator_shell::cal_ln(long double input)
{
	if (input <= 0)
	{
		string e = "invalid input for function ln";
		throw e;
	}
	long double answer = log(input);
	return answer;
}
long double calculator_shell::cal_lg(long double input)
{
	if (input <= 0) {
		string e = "invalid input for function lg";
		throw e;
	}
	long double answer = log10(input);
	return answer;
}
long double calculator_shell::cal_sqrt(long double input)
{
	if (input < 0)
	{
		string e = "invalid input for function sqrt";
		throw e;
	}
	long double answer = sqrt(input);
	return answer;
}
long double calculator_shell::cal_abs(long double input)
{
	long double answer = abs(input);
	return answer;
}
long double calculator_shell::cal_sin(long double input)
{
	long double answer = sin(input);
	return answer;
}
long double calculator_shell::cal_cos(long double input)
{
	long double answer = cos(input);
	return answer;
}
long double calculator_shell::cal_tan(long double input)
{
	long double answer = tan(input);
	return answer;
}
long double calculator_shell::cal_sinh(long double input)
{
	long double answer = sinh(input);
	return answer;
}
long double calculator_shell::cal_cosh(long double input)
{
	long double answer = cosh(input);
	return answer;
}
long double calculator_shell::cal_tanh(long double input)
{
	long double answer = tanh(input);
	return answer;
}
long double calculator_shell::cal_arcsin(long double input)
{
	if (input < -1 || input > 1)
	{
		string e = "invalid input for function arcsin";
		throw e;
	}
	long double answer = asin(input);
	return answer;
}
long double calculator_shell::cal_arccos(long double input)
{
	if (input < -1 || input > 1)
	{
		string e = "invalid input for function arccos";
		throw e;
	}
	long double answer = acos(input);
	return answer;
}
long double calculator_shell::cal_arctan(long double input)
{
	long double answer = atan(input);
	return answer;
}
long double calculator_shell::cal_arcsinh(long double input)
{
	long double answer = asinh(input);
	return answer;
}
long double calculator_shell::cal_arccosh(long double input)
{
	if (input < 1)
	{
		string e = "invalid input for funtion arccosh";
		throw e;
	}
	long double answer = acosh(input);
	return answer;
}
long double calculator_shell::cal_arctanh(long double input)
{
	if (input <= -1 || input >= 1)
	{
		string e = "invalid input for funtion arctanh";
		throw e;
	}

	long double answer = atanh(input);
	return answer;
}
long double calculator_shell::cal_factor(long double input)
{
	long max = input;
	long double answer = 1;
	if (max == 0)
		return 1;
	if ((input - max) != 0 || max < 0)
	{
		string e = "invalid input for funtion factor";
		throw e;
	}
	else
		for (int i = 1; i < max + 1; i++)
			answer = answer * i;
	return answer;
}
long double calculator_shell::cal_percen(long double input)
{
	long double answer = input * 0.01;
	return answer;
}


