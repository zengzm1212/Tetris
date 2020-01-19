#pragma once
#include <qgraphicsitem.h>

// ������ʾ�ĵ����������ĸ����������һ��ͼ�νڵ㣩
// Ϊ�˱���ͬһ����������С���鷢����ײ��
// С����Ĵ�Сʵ��Ϊ19.5*19.5������С������ϱ�ˢ�Ŀ�Ⱥ�Ϊ20 * 20

class Box :  public QGraphicsItem   //a base class for all graphics items that require signals, slots and properties
{
public:
    Box(size_t row, size_t column, const QColor &color = Qt::red);
    ~Box();

    void SetColor(QColor color) { m_color = color; }

    //Ϊ���ṩһ����Χ�ı߽����
    virtual QRectF boundingRect() const;
    //QGraphicsView���ã��ڱ�������ϵͳ�л�����
    virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    //���¶��������״��Ĭ�ϵ���boundingRect��ȡ��ľ�����״����    ���������������˵û�ã���Ϊ���Լ������ཻ���ж�
    virtual QPainterPath shape() const;

private:
    QColor m_color;
    // �����Դ���λ����Ϣ�����Բ���Ҫ����������λ��
};

