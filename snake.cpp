#include "snake.h"

#include <QDebug>
#include <QInputEvent>
#include <QPainter>

Snake::Snake(QPoint position)
    : pos {position},
      dir {direction::Stop},
      timer {new QTimer}
{

    connect(timer, &QTimer::timeout,
            this, &Snake::movement);
    timer->start(100);
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

void Snake::setDirection(Snake::direction direction)
{
    dir = direction;
}

Snake::direction Snake::getDirection()
{
    return dir;
}

void Snake::movement()
{
    prepareGeometryChange();
    switch (dir) {
    case direction::Up:
        pos.ry() -= shift;
        break;
    case direction::Down:
        pos.ry() += shift;
        break;
    case direction::Left:
        pos.rx() -= shift;
        break;
    case direction::Right:
        pos.rx() += shift;
        break;
    default:
        break;
    }
    pos.rx() = pos.rx()<=0 ? 400 : pos.rx()%400;
    pos.ry() = pos.ry()<=0 ? 300 : pos.ry()%300;
}
