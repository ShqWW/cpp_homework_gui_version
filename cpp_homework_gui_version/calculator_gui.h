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
class calculator_gui : public QWidget, private calculator_shell
{
	Q_OBJECT
public:
	calculator_gui(QWidget* parent = 0);
	//~calculator_gui();
private:
	QLineEdit* input;
	QLineEdit* output;
	QFont font;
	QPushButton* confirm;
	vector<QString> input_str;

	vector<QString> btn_fun_name = {
		"sqrt", "cos", "sin", "tan",
		"arcsin", "arccos", "arctan", "sinh",
		"cosh", "tanh", "arcsinh", "arccosh",
		"arctanh", "lg", "ln", "abs"
	};
	vector<QString> btn_num_name = {
		"!","1","2","3","+","del",
		"%","4","5","6","-","(",
		"pi","7","8","9","*",")",
		"e","ans","0","^","/","="
	};

	QShortcut* key;//创建一个快捷键"Key_Return"键
	QTextCodec* codec = QTextCodec::codecForName("GBK");//中文字体管理 

	void get_input(string);
	void set_lineedit();
	void set_button();
	string calculate();

private slots:
	void get_outcome();
	void get_input();
};

