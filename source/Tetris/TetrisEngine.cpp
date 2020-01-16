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
    // �Ƚ���һ�β������ж���β����Ƿ�����Ҫ�� 
    KeyTransform(pBrick, keyAction);
    // ��pBrick��״̬����m_currentBrick��
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            // ��Brick��status�д洢��״̬��Ϣ��������
            m_currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            // ����ǰ״̬������ײ��� (Խ����ͻ)
            if (IsBeyoundBoundary(pBrick) ||  // �Ƿ�Խ��
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
            // ��Brick��status�д洢��״̬��Ϣ��������
            m_currentBrick[i][j] = ((pBrick->GetStatus()) >> (12 - 4 * i + 3 - j)) & 1;
            // ����ǰ״̬������ײ���
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