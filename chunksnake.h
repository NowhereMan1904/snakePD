#ifndef CHUNKSNAKE_H
#define CHUNKSNAKE_H

#include <QGraphicsItem>

class ChunkSnake : public QGraphicsItem
{
public:
    ChunkSnake(const QPoint&);
    ~ChunkSnake() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    QPoint position() const;
    QPoint& position();

    static QColor color;

private:
    QPoint pos;
};

#endif // CHUNKSNAKE_H
