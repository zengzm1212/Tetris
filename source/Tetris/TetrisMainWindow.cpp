#include "TetrisMainWindow.h"

TetrisMainWindow::TetrisMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

    // 绑定界面的按键
    connect(ui.m_startButton, SIGNAL(clicked()), this, SLOT(StartGame()));
    connect(ui.m_pauseButton, SIGNAL(clicked()), this, SLOT(PauseGame()));
    connect(ui.m_restartButton, SIGNAL(clicked()), this, SLOT(RestartGame()));
    connect(ui.m_overButton, SIGNAL(clicked()), this, SLOT(StopGame()));
}


void TetrisMainWindow::StartGame()
{

}
void TetrisMainWindow::PauseGame()
{

}
void TetrisMainWindow::RestartGame()
{

}
void TetrisMainWindow::StopGame()
{

}