#include "TetrisEngine.h"


TetrisEngine::TetrisEngine()
{
}


TetrisEngine::~TetrisEngine()
{
}

int TetrisEngine::ComputeNextStatus(EnKeyAction keyAction)
{
    if (keyAction == EnKeyAction::LEFT)
    {
        MoveLeft();
    }
    else if (keyAction == EnKeyAction::RIGHT)
    {
        MoveRight();
    }
    else if (keyAction == EnKeyAction::DOWN)
    {
        MoveDown();
    }
    else
    {
        UpRotate();
    }
    return 0;
}

