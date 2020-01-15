#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TetrisMainWindow.h"

class TetrisMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	TetrisMainWindow(QWidget *parent = Q_NULLPTR);


public slots:
    // 针对四个按键的槽函数
    void StartGame();
    void PauseGame();
    void RestartGame();
    void StopGame();

private:
	Ui::TetrisMainWindowClass ui;
    // 记录游戏状态
    bool m_isGamePause;
    bool m_isGameOver;
};
