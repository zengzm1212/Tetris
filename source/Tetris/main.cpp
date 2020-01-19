#include "TetrisMainWindow.h"
#include <QtWidgets/QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    //设置随机数的源
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	TetrisMainWindow w;
	w.show();
	return a.exec();
}
