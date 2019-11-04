#include "calculator_gui.h"
#include <QApplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	calculator_gui Calculator;
    Calculator.jump_out();
	return app.exec();
}

