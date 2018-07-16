#ifndef CHUNKSNAKE_H
#define CHUNKSNAKE_H

#include <QGraphicsItem>
#include <QJsonObject>

class ChunkSnake : public QGraphicsItem
{
public:
    ChunkSnake();
    ChunkSnake(const QPoint&);
    ~ChunkSnake() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    QPoint position() const;
    QPoint& position();

    void setColor(QColor);

    void readJSON(const QJsonObject &json);
    void writeJSON(QJsonObject &json) const;

private:
    QPoint pos;
    QColor color;
};

#endif // CHUNKSNAKE_H
