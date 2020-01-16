#include "TetrisEngine.h"
#include "Brick.h"

TetrisEngine::TetrisEngine()
{
}


TetrisEngine::~TetrisEngine()
{
}

void TetrisEngine::KeyTransform(Brick* pBrick, EnKeyAction keyAction)
{
    if (keyAction == EnKeyAction::LEFT)
    {
        pBrick->SetBrickColumn(pBrick->GetBrickColumn() - 1);
    }
    else if (keyAction == EnKeyAction::RIGHT)
    {
        pBrick->SetBrickColumn(pBrick->GetBrickColumn() + 1);
    }
    else if (keyAction == EnKeyAction::DOWN)
    {
        pBrick->SetBrickRow(pBrick->GetBrickRow() + 1);
    }
    else if (keyAction == EnKeyAction::UP)
    {
        pBrick->Rotate();
    }
}

void TetrisEngine::ReverseTransform(Brick* pBrick, EnKeyAction keyAction)
{
    if (keyAction == EnKeyAction::LEFT)
    {
        pBrick->SetBrickColumn(pBrick->GetBrickColumn() + 1);
    }
    else if (keyAction == EnKeyAction::RIGHT)
    {
        pBrick->SetBrickColumn(pBrick->GetBrickColumn() - 1);
    }
    else if (keyAction == EnKeyAction::DOWN)
    {
        pBrick->SetBrickRow(pBrick->GetBrickRow() - 1);
    }
    else if (keyAction == EnKeyAction::UP)
    {
        pBrick->Rotate();
        pBrick->Rotate();
        pBrick->Rotate();
    }
}

bool TetrisEngine::NextStepIsReasonable(int** pBackgroundMatrix, Brick* pBrick, EnKeyAction keyAction)
{
    // 先进行一次操作，判断这次操作是否满足要求 
    KeyTransform(pBrick, keyAction);
    // 将pBrick的状态放置m_currentBrick中
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            // 将Brick中status中存储的状态信息解析出来
            m_currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            // 将当前状态进行碰撞检测 (越界或冲突)
            if (IsBeyoundBoundary(pBrick) ||  // 是否越界
                (pBackgroundMatrix[pBrick->GetBrickRow() + i][pBrick->GetBrickColumn() - j] == 1
                    && m_currentBrick[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}

bool TetrisEngine::IsBeyoundBoundary(Brick* pBrick)
{
    for (size_t i = 0; i < 4; ++i)
    {
        bool flag = false;
        for (size_t j = 0; j < 4; ++j)
        {
            // 将Brick中status中存储的状态信息解析出来
            m_currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            // 将当前状态进行碰撞检测
            if (m_currentBrick[i][j] && 
                ((pBrick->GetBrickRow() + i) < 0 
                    || (pBrick->GetBrickRow() + i) >= WINDOW_WIDTH
                    || (pBrick->GetBrickColumn() - j) >= WINDOW_HEIGHT
                    ))
            {
                return false;
            }
        }
    }
    return true;
}