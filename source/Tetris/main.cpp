#include "TetrisMainWindow.h"
#include <QtWidgets/QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    //�����������Դ
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	TetrisMainWindow w;
	w.show();
	return a.exec();
}
