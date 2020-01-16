#pragma once

#include "MacroDefines.h"

class Brick;

// �����ר�����ڼ����ƶ�����ײ����
class TetrisEngine
{
public:
    TetrisEngine();
    ~TetrisEngine();

    // ����pBrick����keyAction�������Ƿ����pBackgroundMatrixΪ��ǰ״̬�µı�������
    // ע��ú���������һ��Brick
    bool NextStepIsReasonable(int** pBackgroundMatrix, Brick* pBrick, EnKeyAction keyAction);
    // ��pBrick����һ��keyAction����
    void KeyTransform(Brick* pBrick, EnKeyAction keyAction);
    void ReverseTransform(Brick* pBrick, EnKeyAction keyAction);

private:
    bool IsBeyoundBoundary(Brick* pBrick);

private:
    bool m_currentBrick[4][4];     // ���ڻ������,Brickת����bool�;����ʾ��1��ʾ�з����λ��  ��Ϊ�ӵ���&����Ľ��
    bool m_isFrozen;               // �Ƿ�Ϊ����״̬������֮���������ƶ�����������Ҫ�������У�
};

