#pragma once

#include "MacroDefines.h"
#include <vector>

class Brick;

// �����ר�����ڼ����ƶ�����ײ����
// �����ݲ���в���
class TetrisEngine
{
public:
    TetrisEngine();
    ~TetrisEngine();

    // ����pBrick����keyAction�������Ƿ����pBackgroundMatrixΪ��ǰ״̬�µı�������
    // ע��ú���������һ��Brick
    static bool NextStepIsReasonable(int** pBackgroundMatrix, Brick* pBrick, EnKeyAction keyAction);
    // ��pBrick����һ��keyAction����
    static void KeyTransform(Brick* pBrick, EnKeyAction keyAction);
    static void ReverseTransform(Brick* pBrick, EnKeyAction keyAction);

    static bool ClearFullRow(int** pBackgroundMatrix);

private:
    static bool IsBeyoundBoundary(Brick* pBrick);
};

