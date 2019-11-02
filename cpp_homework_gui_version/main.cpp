#include "calculator_gui.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	calculator_gui calculator;
	calculator.show();
	return app.exec();
}