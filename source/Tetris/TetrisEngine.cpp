#include "TetrisEngine.h"
#include "Brick.h"

namespace
{
    bool IsIntInVector(std::vector<int> vct, int n)
    {
        for (std::vector<int>::iterator itor = vct.begin(); itor != vct.end(); ++itor)
        {
            if (*itor == n)
                return true;
        }
        return false;
    }
}

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
    // 如果越界
    if (IsBeyoundBoundary(pBrick)) 
    {
        ReverseTransform(pBrick, keyAction);
        return false;
    }

    // 将pBrick的状态放置currentBrick中
    bool currentBrick[4][4];
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            // 将Brick中status中存储的状态信息解析出来
            currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            // 将当前状态进行碰撞检测
            int r = pBrick->GetBrickRow() - 3 + i;
            int c = pBrick->GetBrickColumn() + j;
            if ((pBackgroundMatrix[pBrick->GetBrickRow() - 3 + i][pBrick->GetBrickColumn() + j] == 1)
                    && currentBrick[i][j])
            {
                ReverseTransform(pBrick, keyAction);
                return false;
            }
        }
    }
    ReverseTransform(pBrick, keyAction);
    return true;
}

bool TetrisEngine::IsBeyoundBoundary(Brick* pBrick)
{
    if (pBrick->GetBrickRow() >= WINDOW_HEIGHT || pBrick->GetBrickColumn() < 0)
        return true;

    bool currentBrick[4][4];
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            // 将Brick中status中存储的状态信息解析出来
            currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            if (currentBrick[i][j] && (pBrick->GetBrickColumn() + j) >= WINDOW_WIDTH)
                return true;
        }
    }
    return false;
}

bool TetrisEngine::ClearFullRow(int** pBackgroundMatrix)
{
    std::vector<int> clearRows;
    for (size_t i = 0; i < WINDOW_HEIGHT; ++i)
    {
        std::vector<int> rowBoxs;
        for (size_t j = 0; j < WINDOW_WIDTH; ++j)
        {
            if (pBackgroundMatrix[i][j] == 1)
                rowBoxs.push_back(pBackgroundMatrix[i][j]);
        }
        if (rowBoxs.size() == 10)
        {
            clearRows.push_back(i);
        }
    }
    if (clearRows.size() == 0)
        return false;

    int clearRow = clearRows.back();       // 需要删除的行
    int maintainRow = clearRow - 1; // 需要消除的行的上一行
    for (; clearRow >= 0; --clearRow)
    {
        while (maintainRow >= 0)
        {
            if (IsIntInVector(clearRows, maintainRow))
            {
                maintainRow--;
                continue;
            }
            for (size_t clearColumn = 0; clearColumn < WINDOW_WIDTH; ++clearColumn)
            {
                pBackgroundMatrix[clearRow][clearColumn] = pBackgroundMatrix[maintainRow][clearColumn];
            }
            maintainRow--;
            clearRow--;
        }
        // 当上面的方块都落下后，落下后的空间用0填充
        for (size_t clearColumn = 0; clearColumn < WINDOW_WIDTH; ++clearColumn)
        {
            pBackgroundMatrix[clearRow][clearColumn] = 0;
        }
    }
    return true;
}