#pragma once

#include "MacroDefines.h"

class Brick;

// 这个类专门用于计算移动，碰撞检测等
// 对数据层进行操作
class TetrisEngine
{
public:
    TetrisEngine();
    ~TetrisEngine();

    // 方块pBrick进行keyAction操作后是否合理，pBackgroundMatrix为当前状态下的背景矩阵
    // 注意该函数操作了一步Brick
    static bool NextStepIsReasonable(int** pBackgroundMatrix, Brick* pBrick, EnKeyAction keyAction);
    // 将pBrick进行一步keyAction操作
    static void KeyTransform(Brick* pBrick, EnKeyAction keyAction);
    static void ReverseTransform(Brick* pBrick, EnKeyAction keyAction);

private:
    static bool IsBeyoundBoundary(Brick* pBrick);
};

