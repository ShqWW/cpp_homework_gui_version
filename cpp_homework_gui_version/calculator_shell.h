#pragma once
#include <string>
#include <stdexcept>
#include <deque>
#include <unordered_map>
#include <cmath>
#include<iterator>
#include<sstream>
using namespace std;

class calculator_shell
{
public:
	calculator_shell();
	//handle the arithmetical expression
	void get_expression(string);// get the original expression
	void inver_expression();//transfer the original expression to postfix expression
	void output_inver_expression();
	string cal_outcome();//calculate the posrfix expression

private:
	string expression;//the original expression
	string Ans;//last calculated outcome
	long double ans;
	deque<string> postfix_expression;//the postfix expression used for calculating
	deque<string> symbol;//stack:save the number
	deque<long double> number;//stack:save the number 
	unordered_map<string, int> symbol_prio;//the piority of the symbol
	unordered_map<string, long double> const_sym;//the piority of the symbol
	unordered_map<string, long double(calculator_shell::*)(long double, long double)> cal_list;
	unordered_map<string, long double(calculator_shell::*)(long double)> fun_list;//call the function accroding to the function name
	
	void restart();
	//basic calculation:+, -, *, /, ^
	long double cal_add(long double, long double);
	long double cal_minus(long double, long double);
	long double cal_plus(long double, long double);
	long double cal_devi(long double, long double);
	long double cal_pow(long double, long double);
	//all kinds of math function with exception we need 
	long double cal_lg(long double);
	long double cal_ln(long double);
	long double cal_sqrt(long double);
	long double cal_abs(long double);
	long double cal_sin(long double);
	long double cal_cos(long double);
	long double cal_tan(long double);
	long double cal_arcsin(long double);
	long double cal_arccos(long double);
	long double cal_arctan(long double);
	long double cal_sinh(long double);
	long double cal_cosh(long double);
	long double cal_tanh(long double);
	long double cal_arcsinh(long double);
	long double cal_arccosh(long double);
	long double cal_arctanh(long double);
	long double cal_factor(long double);///!
	long double cal_percen(long double);///%
};
