#include "fruit.h"

#include <QRandomGenerator>
#include <QPainter>

Fruit::Fruit()
{
    int x = QRandomGenerator::global()->bounded(1,40);
    int y = QRandomGenerator::global()->bounded(1,30);
    pos = QPoint{x*10, y*10};
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
