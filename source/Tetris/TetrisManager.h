#pragma once

#include "MacroDefines.h"
#include <QObject>

class QKeyEvent;
class QTimer;
class QGraphicsScene;

class Brick;
class TetrisEngine;

class TetrisManager : public QObject
{
    Q_OBJECT
public:
    TetrisManager();
    ~TetrisManager();
    //初始化整个场景的矩阵
    bool InitBackgroundMatrix(int** &pMatrix); 


    // 接受处理键盘事件
    void ReactKeyEvent(QKeyEvent* e);
    
    void Move(EnKeyAction keyAction);

    void StartGame();
    void PauseGame();
    void RestartGame();
    void StopGame();

signals:
    // 响应按键，更新方块位置
    void UpdateBoxPosition(Brick* pBrick, EnKeyAction keyAction);
    void ChangeBrickToBackground(Brick* pBrick);
    void UpdateBackground();

public slots:
    void MoveDownOneStep();

public:
    int** GetBackgroundMatrix() { return m_pBackgroundpMatrix; }
    void SetBackgroundMatrix(int** pMatrix) { m_pBackgroundpMatrix = pMatrix; }
    Brick* GetBrick() { return m_pBrick; }
    void SetBrick(Brick* pBrick) { m_pBrick = pBrick; }

private: // 工具函数
    //用于释放动态分配的内存
    void deleteMatrix(int** pMatrix); 

private:
    QTimer* m_pTimer;
    int** m_pBackgroundpMatrix;     // 背景矩阵
    Brick* m_pBrick;                // 正在移动的方块数据
};

