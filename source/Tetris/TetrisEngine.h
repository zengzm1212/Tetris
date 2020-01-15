#pragma once

#include "MacroDefines.h"

class TetrisEngine
{
public:
    TetrisEngine();
    ~TetrisEngine();

    int ComputeNextStatus(EnKeyAction keyAction); //根据键盘输入计算下一状态

    void MoveLeft() {};
    void MoveRight() {};
    void MoveDown() {};
    void UpRotate() {};

};

