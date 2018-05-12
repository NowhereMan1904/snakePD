#include "fruit.h"

#include <QPainter>
#include <QRandomGenerator>

Fruit::Fruit(QPoint p)
    : pos {p}
{
    auto r = QRandomGenerator::global()->bounded(100,256);
    auto g = QRandomGenerator::global()->bounded(100,256);
    auto b = QRandomGenerator::global()->bounded(100,256);
    color = QColor{r,g,b};
}

QRectF Fruit::boundingRect() const
{
    qreal penWidth = 12;
    return QRectF{pos.x() - penWidth/2, pos.y() - penWidth/2,
                  pos.x() + penWidth, pos.y() + penWidth};
}

void Fruit::paint(QPainter* painter,
                  const QStyleOptionGraphicsItem*,
                  QWidget*)
{
    painter->setPen(QPen{Qt::NoPen});
    painter->setBrush(QBrush{color});
    painter->drawEllipse(pos, 6, 6);
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

QColor Fruit::getColor() const
{
    return color;
}
