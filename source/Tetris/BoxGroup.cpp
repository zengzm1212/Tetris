#include "BoxGroup.h"



BoxGroup::BoxGroup()
{
    //使得方块组支持键盘操作
    setFlags(QGraphicsItem::ItemIsFocusable);
}


BoxGroup::~BoxGroup()
{
}
