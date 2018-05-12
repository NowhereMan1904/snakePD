#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsObject>
#include<QPoint>

class Fruit : public QGraphicsObject
{
    Q_OBJECT

public:
    Fruit(QPoint);
    ~Fruit() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    QPoint position() const;
    QPoint& position();

    QColor getColor() const;

private:
    QPoint pos; // position of the fruit
    QColor color;

};

#endif // FRUIT_H
