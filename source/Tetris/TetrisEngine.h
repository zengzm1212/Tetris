#pragma once

#include "MacroDefines.h"

class Brick;

// 这个类专门用于计算移动，碰撞检测等
class TetrisEngine
{
public:
    TetrisEngine();
    ~TetrisEngine();

    // 方块pBrick进行keyAction操作后是否合理，pBackgroundMatrix为当前状态下的背景矩阵
    // 注意该函数操作了一步Brick
    bool NextStepIsReasonable(int** pBackgroundMatrix, Brick* pBrick, EnKeyAction keyAction);
    // 将pBrick进行一步keyAction操作
    void KeyTransform(Brick* pBrick, EnKeyAction keyAction);
    void ReverseTransform(Brick* pBrick, EnKeyAction keyAction);

private:
    bool IsBeyoundBoundary(Brick* pBrick);

private:
    bool m_currentBrick[4][4];     // 用于缓存计算,Brick转化成bool型矩阵表示，1表示有方块的位置  因为接的是&运算的结果
    bool m_isFrozen;               // 是否为冻结状态（冻结之后不允许再移动，并计算需要消除的行）
};

