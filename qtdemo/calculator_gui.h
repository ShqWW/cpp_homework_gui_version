#pragma once

#include <QLabel>
#include <QApplication>
#include <QLineEdit>
#include <QWidget>
#include <iostream>
#include <QMainWindow>
#include <QPushButton>
#include "calculator_shell.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QList>
#include <qtextcodec.h> 
#include <QShortcut>
class calculator_gui : public QWidget, public calculator_shell
{
	//Q_OBJECT
	Q_OBJECT
public:
	QTextCodec* codec = QTextCodec::codecForName("GBK");//修改这两行 
	calculator_gui(QWidget* parent = 0);
	QLineEdit* input;
	QLineEdit* output;
	QFont font;
	QPushButton* confirm;
	void get_input(string);
	string calculate();
	QShortcut* key;//创建一个快捷键"Key_Return"键
private:
	void set_lineedit();
	void set_button();
private slots:
	void get_exp();
};

