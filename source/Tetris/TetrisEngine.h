#pragma once

#include "MacroDefines.h"

class TetrisEngine
{
public:
    TetrisEngine();
    ~TetrisEngine();

    int ComputeNextStatus(EnKeyAction keyAction); //���ݼ������������һ״̬

    void MoveLeft() {};
    void MoveRight() {};
    void MoveDown() {};
    void UpRotate() {};

};

