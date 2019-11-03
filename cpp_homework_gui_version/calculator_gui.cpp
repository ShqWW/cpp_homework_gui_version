#include "calculator_gui.h"
#include <string>
#include <QApplication>
#include <algorithm>
//using namespace std;

calculator_gui::calculator_gui(QWidget* parent) :QWidget(parent)
{
	setMaximumSize(16777215,16777215);
	setMinimumSize(800, 500);
	setWindowTitle(codec->toUnicode("破逆子"));
	setWindowIcon(QIcon("./Calculator.ico"));
	set_lineedit();
	set_button();
}

void calculator_gui::get_input(string s)
{
	get_expression(s);
}
string calculator_gui::calculate()
{
	try
	{
		inver_expression();
		return cal_outcome();
	}
	catch (string error)
	{
		throw(error);
	}
}

void calculator_gui::set_lineedit()
{
	input = new QLineEdit(this);
	output = new QLineEdit(this);
	input->setAlignment(Qt::AlignRight);
	input->resize(790, 80);
	input->move(10, 40);
	input->setStyleSheet("border-width: 3px;border-radius:15px;border-style:solid;border-color: rgb(255, 170, 0);background-color: rgb(255, 255, 255);color:rgb(0,0,0)");
	output->setAlignment(Qt::AlignRight);
	output->resize(790, 80);
	output->move(10, 200);
	output->setStyleSheet("border-width: 3px;border-radius:15px;border-style:solid;border-color: rgb(255, 170, 0);background-color: rgb(255, 255, 255);color:rgb(0,0,0)");
	font.setPointSize(40);
	input->setFont(this->font);
	output->setFont(this->font);
	output->setEnabled(false);
}
void calculator_gui::set_button()
{
	QPushButton* btn;
	int x = 30, y = 400, btn_wid = 80, btn_hei = 30;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			btn=new QPushButton(this);
			btn->setText(btn_fun_name[i*4+j]);
			btn->resize(btn_wid, btn_hei);
			btn->move(x + btn_wid * j, y + btn_hei * i);
			connect(btn, SIGNAL(clicked()), this, SLOT(get_input()));
		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 6; j++)
		{
			btn= new QPushButton(this);
			btn->setText(btn_num_name[i * 6 + j]);
			btn->resize(btn_wid, btn_hei);
			btn->move(x + btn_wid * j + 350, y + btn_hei * i);
			connect(btn, SIGNAL(clicked()), this, SLOT(get_input()));
		}
	key = new QShortcut(QKeySequence(Qt::Key_Return), this);
	confirm = new QPushButton(this);
	confirm->setShortcut(Qt::Key_Enter);
	connect(key, SIGNAL(activated()), this, SLOT(get_outcome()));//连接到指定槽函数
	connect(confirm, SIGNAL(clicked()), this, SLOT(get_outcome()));
	confirm->setText(codec->toUnicode("计算"));
	confirm->move(750, 300);
	//output->resize(60, 40);
	font.setPointSize(20);
	confirm->setFont(this->font);
	//output->setStyleSheet("border-width: 3px;border-radius:15px;border-style:solid;border-color: rgb(255, 170, 0);background-color: rgb(255, 255, 255);color:rgb(0,0,0)");
}
void calculator_gui::get_outcome()
{
	QString s = input->text();
	if (s == "")
	{
		output->setText("");
	}
	else
	{
		try
		{
			get_expression(s.toStdString());
			s = QString::fromStdString(calculate());
			output->setText(s);
		}
		catch (string error)
		{
			output->setText(QString::fromStdString(error));
		}
	}
}
void calculator_gui::get_input()
{
	QPushButton* btn = dynamic_cast<QPushButton*>(sender());
	if (std::find(btn_fun_name.begin(), btn_fun_name.end(), btn->text()) != btn_fun_name.end())
	{
		input_str.push_back(btn->text() + "(");
	}
	else if (std::find(btn_num_name.begin(), btn_num_name.end(), btn->text()) != btn_num_name.end())
	{
		if (btn->text() == "del" && !input_str.empty())
			input_str.pop_back();
		else if (btn->text() == "del" && input_str.empty())
			return;
		else if (btn->text() == "=")
		{
			get_outcome();
			return;
		}
		else 
			input_str.push_back(btn->text());
	}
	std::vector<QString>::iterator index = input_str.begin();
	input->clear();
	while (index != input_str.end())
	{
		input->insert(*index);
		index ++;
	}
}