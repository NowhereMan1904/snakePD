#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
#include <QTimer>
#include <QObject>

class Snake : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum class direction { Up, Down, Left, Right, Stop };

    Snake(QPoint position);

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    QPoint* position();

    void setDirection(Snake::direction);
    direction getDirection();

public slots:
    void movement();

private:
    constexpr static int shift = 10;
    QPoint pos;
    enum direction dir;
    QTimer* timer;
};

#endif // SNAKE_H
