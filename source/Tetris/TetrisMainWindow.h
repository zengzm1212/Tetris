#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TetrisMainWindow.h"
#include "MacroDefines.h"

class TetrisManager;
class Box;
class Brick;

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
    virtual void keyPressEvent(QKeyEvent* e);

public slots:
    // 针对四个按键的槽函数
    void StartGame();
    void PauseGame();
    void RestartGame();
    void StopGame();
    
    void DisplayUiView();
    void ClearUiView();

public:
    void UpdateUiBoxPosition(EnKeyAction keyAction, Brick* pBrick);    // 下、左、右移后更新位置
    void UpdateRotatedBoxPosition(Brick* pBrick);      // 旋转后更新位置
    void UpdateBackgroundBoxs();    // 更新背景

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

    TetrisManager* m_pTetrisManager;
    // 存储整个背景中需要显示的Box节点   用 pBackgroundBoxs[i*row+j]标志[i,j]位置处的节点
    Box* m_pBackgroundBoxs[WINDOW_HEIGHT * WINDOW_WIDTH];
    // 存储正在下落形状的4个方格
    Box* m_p4Boxs[4];
};
