#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsObject>
#include<QPoint>

class Fruit : public QGraphicsObject
{
    Q_OBJECT

public:
    Fruit();
    ~Fruit() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    QPoint position() const;
    QPoint& position();

private:
    QPoint pos; // position of the fruit

};

#endif // FRUIT_H
