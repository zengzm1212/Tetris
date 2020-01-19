#pragma once
#include <qgraphicsitem.h>

// 用于显示的单个正方向（四个正方形组成一个图形节点）
// 为了避免同一个方块组内小方块发生碰撞，
// 小方块的大小实际为19.5*19.5，但是小方块加上笔刷的宽度后为20 * 20

class Box :  public QGraphicsItem   //a base class for all graphics items that require signals, slots and properties
{
public:
    Box(size_t row, size_t column, const QColor &color = Qt::red);
    ~Box();

    void SetColor(QColor color) { m_color = color; }

    //为项提供一个外围的边界矩形
    virtual QRectF boundingRect() const;
    //QGraphicsView调用，在本地坐标系统中绘制项
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    //重新定义项的形状，默认调用boundingRect获取项的矩形形状轮廓    对于我这个程序来说没用，因为是自己进行相交性判断
    virtual QPainterPath shape() const;

private:
    QColor m_color;
    // 基类自带了位置信息，所以不需要再设置坐标位置
};

