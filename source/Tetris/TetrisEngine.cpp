#include "TetrisEngine.h"
#include "Brick.h"

namespace
{
    void FindBackMatrix(int res[WINDOW_HEIGHT][WINDOW_WIDTH], int** pMatrix)
    {
        for (size_t i = 0; i < WINDOW_HEIGHT; ++i)
        {
            for (size_t j = 0; j < WINDOW_WIDTH; j++)
            {
                res[i][j] = pMatrix[i][j];
            }
        }
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
    int res[WINDOW_HEIGHT][WINDOW_WIDTH];
    FindBackMatrix(res, pBackgroundMatrix);

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