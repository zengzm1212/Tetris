#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TetrisMainWindow.h"

class TetrisMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	TetrisMainWindow(QWidget *parent = Q_NULLPTR);


public slots:
    // ����ĸ������Ĳۺ���
    void StartGame();
    void PauseGame();
    void RestartGame();
    void StopGame();

private:
	Ui::TetrisMainWindowClass ui;
    // ��¼��Ϸ״̬
    bool m_isGamePause;
    bool m_isGameOver;
};
