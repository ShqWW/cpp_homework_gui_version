#include "calculator_gui.h"

int main(int argc, char* argv[])
{
	//有且只有一个应用程序类的对象
	QApplication app(argc, argv);
	calculator_gui calculator;
	calculator.show();
	return app.exec();
}