#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsItem>

class Fruit : public QGraphicsItem
{
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
