#include "snake.h"

#include <QDebug>
#include <QInputEvent>
#include <QPainter>

Snake::Snake(QPoint position)
    : pos {position},
      dir {Direction::Stop}
{

}

QRectF Snake::boundingRect() const
{
    qreal penWidth = 10;
    return QRectF{pos.x() - penWidth/2, pos.y() - penWidth/2,
                  pos.x() + penWidth, pos.y() + penWidth};
}

void Snake::paint(QPainter* painter,
                  const QStyleOptionGraphicsItem*,
                  QWidget*)
{
    painter->setPen(QPen{Qt::white, 10});
    painter->drawPoint(pos);
}

QPoint* Snake::position()
{
    prepareGeometryChange();
    return &pos;
}

void Snake::setDirection(Snake::Direction direction)
{
    dir = direction;
}

Snake::Direction Snake::direction()
{
    return dir;
}

void Snake::movement()
{
    prepareGeometryChange();
    switch (dir) {
    case Direction::Up:
        pos.ry() -= shift;
        break;
    case Direction::Down:
        pos.ry() += shift;
        break;
    case Direction::Left:
        pos.rx() -= shift;
        break;
    case Direction::Right:
        pos.rx() += shift;
        break;
    default:
        break;
    }
    pos.rx() = pos.rx()<=0 ? 400-10 : pos.rx()%400;
    pos.ry() = pos.ry()<=0 ? 300-10 : pos.ry()%300;
}
