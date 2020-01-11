#include "TetrisMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TetrisMainWindow w;
	w.show();
	return a.exec();
}
