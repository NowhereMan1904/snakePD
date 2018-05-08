#ifndef SNAKE_H
#define SNAKE_H

#include <QTimer>
#include <QGraphicsObject>

class Snake : public QGraphicsObject
{
    Q_OBJECT

public:
    enum class Direction { Up, Down, Left, Right, Stop };

    Snake(QPoint position);

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    QPoint* position();

    void setDirection(Snake::Direction);
    Direction direction();

public slots:
    void movement();

private:
    constexpr static int shift = 10;
    QPoint pos;
    enum Direction dir;
};

#endif // SNAKE_H
