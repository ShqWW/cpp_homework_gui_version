#include "calculator_gui.h"

calculator_gui::calculator_gui(QWidget* parent) :QWidget(parent)
{
	//setMaximumSize(16777215,16777215);
	setMaximumSize(1000, 630);
	setMinimumSize(1000, 630);
	setWindowTitle(codec->toUnicode("科学计算器"));
	setWindowIcon(QIcon("./Resources/Calculator.ico"));
	setStyleSheet("background-color: rgb(30, 30, 30)");
	font.setFamily("Comic Sans MS");
	set_lineedit();
	set_button();
	QLabel* image = new QLabel(this);
	QString path = QString("./Resources/cal.png");
	QImage im;
	im.load(path);
	QPixmap px = QPixmap::fromImage(im);
	//show
	image->setPixmap(px);
	image->resize(140, 140);
	image->move(860,210);
}

void calculator_gui::set_lineedit()
{
	error_msg = new QLabel(this);
	error_msg->move(684, 160);
	error_msg->resize(300, 60);
	font.setPointSize(12);
	error_msg->setFont(this->font);
	error_msg->setText("     (^OvO^)  @by Shq Wang");
	error_msg->setStyleSheet("color:rgb(232, 232, 232)");
	input = new QLineEdit(this);
	output = new QLineEdit(this);
	input->setAlignment(Qt::AlignRight);
	input->resize(950, 85);
	input->move(34, 20);
	QString line_set = "border-width: 1px;"
		"border-radius:5px;"
		"border-style:solid;"
		"border-color: rgb(240, 255, 255);"
		"background-color: rgb(240, 255, 255);"
		"color:rgb(0,0,0)";
	input->setStyleSheet(line_set);
	output->setAlignment(Qt::AlignRight);
	output->resize(300, 59);
	output->move(684, 95);
	output->setStyleSheet(line_set);
	font.setPointSize(29);
	input->setFont(this->font);
	font.setPointSize(25);
	output->setFont(this->font);
	input->setEnabled(false);
	output->setEnabled(false);
}
void calculator_gui::set_button()
{
	QPushButton* btn;
	QShortcut* key;
	QString btn_set = "QPushButton{border-width: 1px;"
		"border-radius:6px;"
		"border-style:solid;"
		"border-color: rgb(255, 255, 255);"
		"background-color: rgb(20, 20, 20);"
		"color:rgb(238, 233, 233);}"
		"QPushButton:hover{background-color:rgb(54, 54, 54);}"
		"QPushButton:pressed{background-color:rgb(79, 79, 79);}";
	int x = 30, y = 110, btn_wid = 160, btn_hei = 60;
	font.setPointSize(20);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			btn=new QPushButton(this);
			btn->setText(btn_fun_name[i*4+j]);
			btn->resize(btn_wid, btn_hei);
			btn->move(x + btn_wid * j, y + btn_hei * i);
			btn->setFont(font);
			btn->setStyleSheet(btn_set);
			connect(btn, SIGNAL(clicked()), this, SLOT(btn_input()));
		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 6; j++)
		{
			btn= new QPushButton(this);
			btn->setText(btn_num_name[i * 6 + j]);
			btn->resize(btn_wid, btn_hei);
			btn->move(x + btn_wid * j , y + btn_hei * i + 260);
			btn->setFont(font);
			btn->setStyleSheet(btn_set);
			if (btn->text() == "=")
			{
				key = new QShortcut(QKeySequence(Qt::Key_Return), this);
				connect(key, SIGNAL(activated()), this, SLOT(disp_outcome()));
				key = new QShortcut(QKeySequence(Qt::Key_Enter), this);
				connect(key, SIGNAL(activated()), this, SLOT(disp_outcome()));
				connect(btn, SIGNAL(clicked()), this, SLOT(disp_outcome()));
			}
			else
				connect(btn, SIGNAL(clicked()), this, SLOT(btn_input()));
			if(btn->text() != "="&&btn->text() != "pi"&& btn->text() != "ans")
			{ 
				key = new QShortcut(QKeySequence(btn->text()), this);
				key->setObjectName(btn->text());
				connect(key, SIGNAL(activated()), this, SLOT(key_input()));
			}
		}
	//confirm->setText(codec->toUnicode("计算"));
	btn = new QPushButton(this);
	btn->setFont(font);
	btn->setText("AC");
	btn->resize(btn_wid, btn_hei);
	btn->move(684, 230);
	btn->setStyleSheet(btn_set);
	connect(btn, SIGNAL(clicked()), this, SLOT(clr_sc()));

	btn = new QPushButton(this);
	btn->setFont(font);
	btn->setText("del");
	btn->resize(btn_wid, btn_hei);
	btn->move(684, 230+ btn_hei);
	btn->setStyleSheet(btn_set);
	connect(btn, SIGNAL(clicked()), this, SLOT(btn_input()));
	key = new QShortcut(QKeySequence("Backspace"), this);
	key->setObjectName(btn->text());
	connect(key, SIGNAL(activated()), this, SLOT(key_input()));
	key = new QShortcut(QKeySequence("Delete"), this);
	key->setObjectName(btn->text());
	connect(key, SIGNAL(activated()), this, SLOT(key_input()));
	
}
void calculator_gui::disp_outcome()
{
	QString s = input->text();
	int len = s.size();
	if (len == 0)
	{
		output->clear();
	}
	else
	{
		int match_num = 0;
		for (int i = 0; i < len; i++)
		{
			if (s[i] == '(')
				match_num++;
			else if(s[i] == ')')
				match_num--;
		}
		if(match_num>0)
			while (match_num > 0)
			{
				s.push_back(')');
				match_num--;
			}
		try
		{
			get_expression(s.toStdString());
			inver_expression();
			s = QString::fromStdString(cal_outcome());
			error_msg->setText("     (^OvO^)  @by Shq Wang");
			output->setText(s);
		}
		catch (string error)
		{
			error_msg->setText(QString::fromStdString(error));
			output->clear();
		}
	}
}
void calculator_gui::btn_input()
{
	QPushButton* btn = dynamic_cast<QPushButton*>(sender());
	QString s = btn->text();
	if (s == "del" && !input_str.empty())
		input_str.pop_back();
	else if (s == "del" && input_str.empty())
		return;
	if (std::find(btn_fun_name.begin(), btn_fun_name.end(), s) != btn_fun_name.end())
	{
		input_str.push_back(s + "(");
	}
	else if (std::find(btn_num_name.begin(), btn_num_name.end(), s) != btn_num_name.end())
	{
		input_str.push_back(s);
	}
	std::vector<QString>::iterator index = input_str.begin();
	input->clear();
	while (index != input_str.end())
	{
		input->insert(*index);
		index++;
	}
}
void calculator_gui::key_input()
{
	QShortcut* ky = dynamic_cast<QShortcut*>(sender());
	QString s = ky->objectName();
	if (s == "del" && !input_str.empty())
		input_str.pop_back();
	else if (s == "del" && input_str.empty())
		return;
	if (std::find(btn_fun_name.begin(), btn_fun_name.end(), s) != btn_fun_name.end())
	{
		input_str.push_back(s + "(");
	}
	else if (std::find(btn_num_name.begin(), btn_num_name.end(), s) != btn_num_name.end())
	{
		input_str.push_back(s);
	}
	std::vector<QString>::iterator index = input_str.begin();
	input->clear();
	while (index != input_str.end())
	{
		input->insert(*index);
		index++;
	}
}
void calculator_gui::clr_sc()
{
	while (!input_str.empty())
		input_str.pop_back();
	input->clear();
	output->clear();
	error_msg->setText("     (^OvO^)  @by Shq Wang");
}
void calculator_gui::jump_out()
{
	show();
}