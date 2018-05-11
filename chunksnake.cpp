#include "chunksnake.h"

#include <QPainter>

ChunkSnake::ChunkSnake(const QPoint& position)
    : pos{position}
{

}

QRectF ChunkSnake::boundingRect() const
{
    qreal penWidth = 10;
    return QRectF{pos.x() - penWidth/2, pos.y() - penWidth/2,
                  pos.x() + penWidth, pos.y() + penWidth};
}

void ChunkSnake::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem*,
                       QWidget*)
{
    painter->setPen(QPen{Qt::white, 10});
    painter->drawPoint(pos);
}

QPoint ChunkSnake::position() const
{
    return pos;
}

QPoint& ChunkSnake::setPosition()
{
    prepareGeometryChange();
    return pos;
}
