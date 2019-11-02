#include "calculator_gui.h"
#include <string>
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
	key = new QShortcut(QKeySequence(Qt::Key_Return), this);
	confirm = new QPushButton(this);
	confirm->setShortcut(Qt::Key_Enter);
	connect(key, SIGNAL(activated()), this, SLOT(get_outcome()));//连接到指定槽函数
	connect(confirm, SIGNAL(clicked()), this, SLOT(get_outcome()));
	confirm->setText(codec->toUnicode("计算"));
	confirm->move(650, 400);
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
