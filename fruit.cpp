#include "fruit.h"

#include <QRandomGenerator>
#include <QPainter>

Fruit::Fruit()
{
    int x = QRandomGenerator::global()->bounded(39);
    int y = QRandomGenerator::global()->bounded(29);
    pos = QPoint{x*10, y*10};
}

QPoint Fruit::getPos()
{
    return pos;
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
