#include "Box.h"
#include "MacroDefines.h"
#include <QPainter>

Box::Box(size_t row, size_t column, const QColor &color)
    : m_color(color)
{
    setPos(column * 20 + 45, row * 20 + 45);  // �ж�Ӧ����X����
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
    //������ͼ
    painter->drawPixmap(-BOX_LENGTH / 2, -BOX_LENGTH / 2, BOX_LENGTH, BOX_LENGTH, QPixmap(":/images/box/box.png"));
    painter->setBrush(m_color);

    QColor penColor = Qt::black;     // ���߿����ɫ����Ϊ��ɫ
    // ����ɫ��͸���ȼ�С
    penColor.setAlpha(200);
    painter->setPen(penColor);
    //ʹ�õ�ǰ�ı�ˢ�ͱʻ����ο�
    painter->drawRect(-BOX_LENGTH / 2, -BOX_LENGTH / 2, BOX_LENGTH, BOX_LENGTH);
}

QPainterPath Box::shape() const
{
    QPainterPath path;
    //ȥ����ˢ�Ŀ�ȣ�����ͬһ��������ķ���Ͳ��ᱻ������ײ�����
    path.addRect(-(BOX_LENGTH - PEN_WIDTH) / 2, -(BOX_LENGTH - PEN_WIDTH) / 2, BOX_LENGTH - PEN_WIDTH, BOX_LENGTH - PEN_WIDTH);
    return path;
}