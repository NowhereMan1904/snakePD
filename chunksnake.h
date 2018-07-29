#ifndef CHUNKSNAKE_H
#define CHUNKSNAKE_H

#include <QGraphicsItem>
#include <QJsonObject>

class ChunkSnake : public QGraphicsItem
{
public:
    ChunkSnake() = default;
    ChunkSnake(const QPoint&);
    ~ChunkSnake() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    QPoint getPosition() const;
    void   setPosition(QPoint);

    void setColor(QColor);
    void setX(int);
    void setY(int);

    void readJSON (const QJsonObject&);
    void writeJSON(QJsonObject&) const;

private:
    QPoint pos;
    QColor color;
};

#endif // CHUNKSNAKE_H
