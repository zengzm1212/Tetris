#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TetrisMainWindow.h"

class TetrisMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	TetrisMainWindow(QWidget *parent = Q_NULLPTR);
    ~TetrisMainWindow();

    void initGraphicsViewWidget();

    //void CreateBox();

protected:
    // handle key press event
    //virtual void keyPressEvent(QKeyEvent* e);

public slots:
    // 针对四个按键的槽函数
    void StartGame();
    void PauseGame();
    void RestartGame();
    void StopGame();

private:
	Ui::TetrisMainWindowClass* ui;
    // 记录游戏状态
    bool m_isGamePause;
    bool m_isGameOver;
    // 用于显示的场景
    QGraphicsScene* m_scene;
    // 四条边界线
    QGraphicsLineItem* m_topLine;
    QGraphicsLineItem* m_leftLine;
    QGraphicsLineItem* m_buttomLine;
    QGraphicsLineItem* m_rightLine;
};
