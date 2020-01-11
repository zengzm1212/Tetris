#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TetrisMainWindow.h"

class TetrisMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	TetrisMainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::TetrisMainWindowClass ui;
};
