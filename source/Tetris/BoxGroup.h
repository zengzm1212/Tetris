#pragma once

#include "Box.h"
#include <qgraphicsitem.h>

//�����ĸ������һ��ͼ��
class BoxGroup : public QGraphicsItemGroup
{
public:
    BoxGroup();
    ~BoxGroup();

private:
    QList<Box* > m_boxGroup; //�洢���ĸ�������ʾ�ķ���
};

