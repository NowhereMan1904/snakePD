#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsObject>
#include<QPoint>

class Fruit : public QGraphicsObject
{
    Q_OBJECT

public:
    Fruit();
    QPoint getPos();

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

private:
    QPoint pos; // position of the fruit

};

#endif // FRUIT_H
