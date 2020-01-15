#pragma once

#include "Box.h"
#include <qgraphicsitem.h>

//包含四个方块的一种图形
class BoxGroup : public QGraphicsItemGroup
{
public:
    BoxGroup();
    ~BoxGroup();

private:
    QList<Box* > m_boxGroup; //存储的四个用于显示的方块
};

