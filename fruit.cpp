#include "fruit.h"

#include <QPainter>

Fruit::Fruit(QPoint p)
    : pos {p}
{
}

QRectF Fruit::boundingRect() const
{
    qreal penWidth = 10;
    return QRectF{pos.x() - penWidth/2, pos.y() - penWidth/2,
                  pos.x() + penWidth, pos.y() + penWidth};
}

void Fruit::paint(QPainter* painter,
                  const QStyleOptionGraphicsItem*,
                  QWidget*)
{
    painter->setPen(QPen{Qt::white, 10});
    painter->drawPoint(pos);
}

QPoint Fruit::position() const
{
    return pos;
}

QPoint& Fruit::position()
{
    prepareGeometryChange();
    return pos;
}
