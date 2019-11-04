#pragma once

#include "calculator_shell.h"
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QTextCodec> 
#include <QShortcut>
#include <QString>
#include <QIcon>
#include <vector>
#include <algorithm>

class calculator_gui : private QWidget, private calculator_shell
{
	Q_OBJECT

public:
	calculator_gui(QWidget* parent = 0);
	void jump_out();

private:
	QLineEdit* input;
	QLineEdit* output;
	QFont font;
	QLabel* error_msg;
	QTextCodec* codec = QTextCodec::codecForName("GBK");//中文字体管理
	vector<QString> input_str;

	vector<QString> btn_fun_name = {
		"cos", "sin", "tan","sqrt",
		"arcsin", "arccos", "arctan","abs",
		"sinh","cosh", "tanh", "ln",
		"arcsinh", "arccosh","arctanh","lg"
	};
	vector<QString> btn_num_name = {
		"!","1","2","3","+","^",
		"%","4","5","6","-","(",
		"pi","7","8","9","*",")",
		"e","ans","0",".","/","="
	};

	void set_lineedit();
	void set_button();


private slots:
	void disp_outcome();
	void btn_input();
	void key_input();
	void clr_sc();
};

