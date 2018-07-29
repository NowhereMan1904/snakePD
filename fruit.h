#ifndef FRUIT_H
#define FRUIT_H

#include <QGraphicsItem>
#include <QJsonObject>

class Fruit : public QGraphicsItem
{
public:
    Fruit(QPoint);
    ~Fruit() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    QPoint getPosition() const;
    QColor getColor()    const;

    void readJSON (const QJsonObject&);
    void writeJSON(QJsonObject&) const;

    void move(const QPoint&);

private:
    QPoint pos; // position of the fruit
    QColor color;
};

#endif // FRUIT_H
