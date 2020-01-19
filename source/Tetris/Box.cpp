#include "Box.h"
#include "MacroDefines.h"
#include <QPainter>

Box::Box(size_t row, size_t column, const QColor &color)
    : m_color(color)
{
    setPos(column * 20 + 45, row * 20 + 45);  // 列对应的是X坐标
}

Box::~Box()
{
}

QRectF Box::boundingRect() const
{
    qreal penWidth = PEN_WIDTH;
    return QRectF(-(BOX_LENGTH - penWidth) / 2, -(BOX_LENGTH - penWidth) / 2,
        BOX_LENGTH - penWidth, BOX_LENGTH - penWidth);
}

void Box::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //背景贴图
    painter->drawPixmap(-BOX_LENGTH / 2, -BOX_LENGTH / 2, BOX_LENGTH, BOX_LENGTH, QPixmap(":/images/box/box.png"));
    painter->setBrush(m_color);

    QColor penColor = Qt::black;     // 将边框的样色设置为黑色
    // 将颜色的透明度减小
    penColor.setAlpha(200);
    painter->setPen(penColor);
    //使用当前的笔刷和笔画矩形框
    painter->drawRect(-BOX_LENGTH / 2, -BOX_LENGTH / 2, BOX_LENGTH, BOX_LENGTH);
}

QPainterPath Box::shape() const
{
    QPainterPath path;
    //去除笔刷的宽度，这样同一个方块组的方块就不会被检测出碰撞的情况
    path.addRect(-(BOX_LENGTH - PEN_WIDTH) / 2, -(BOX_LENGTH - PEN_WIDTH) / 2, BOX_LENGTH - PEN_WIDTH, BOX_LENGTH - PEN_WIDTH);
    return path;
}