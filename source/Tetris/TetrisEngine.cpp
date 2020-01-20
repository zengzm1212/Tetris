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
    // �Ƚ���һ�β������ж���β����Ƿ�����Ҫ�� 
    KeyTransform(pBrick, keyAction);
    // ���Խ��
    if (IsBeyoundBoundary(pBrick)) 
    {
        ReverseTransform(pBrick, keyAction);
        return false;
    }

    // ��pBrick��״̬����currentBrick��
    bool currentBrick[4][4];
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            // ��Brick��status�д洢��״̬��Ϣ��������
            currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            // ����ǰ״̬������ײ���
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
            // ��Brick��status�д洢��״̬��Ϣ��������
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

    int clearRow = clearRows.back();       // ��Ҫɾ������
    int maintainRow = clearRow - 1; // ��Ҫ�������е���һ��
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
        // ������ķ��鶼���º����º�Ŀռ���0���
        for (size_t clearColumn = 0; clearColumn < WINDOW_WIDTH; ++clearColumn)
        {
            pBackgroundMatrix[clearRow][clearColumn] = 0;
        }
    }
    return true;
}