#include "calculator_gui.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication *app=new QApplication(argc, argv);
	calculator_gui *À±¼¦Äæ×Ó¼ÆËãÆ÷=new calculator_gui;
    À±¼¦Äæ×Ó¼ÆËãÆ÷->ÅÑÄæµÇ³¡();
	return app->exec();
}