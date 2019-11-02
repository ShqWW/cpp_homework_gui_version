#pragma once

#include "calculator_shell.h"
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QTextCodec> 
#include <QShortcut>
#include <QString>
class calculator_gui : public QWidget, private calculator_shell
{
	Q_OBJECT
public:
	calculator_gui(QWidget* parent = 0);
private:
	QLineEdit* input;
	QLineEdit* output;
	QFont font;
	QPushButton* confirm;
	QShortcut* key;//创建一个快捷键"Key_Return"键
	QTextCodec* codec = QTextCodec::codecForName("GBK");//中文字体管理 

	void get_input(string);
	void set_lineedit();
	void set_button();
	string calculate();

private slots:
	void get_outcome();
};

