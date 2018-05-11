#ifndef SNAKE_H
#define SNAKE_H

#include <QTimer>
#include <QGraphicsObject>
#include <QList>
#include <QHash>

#include "chunksnake.h"

class Snake : public QGraphicsObject
{
    Q_OBJECT

public:
    enum class Direction { Up, Down, Left, Right, Stop };

    Snake(QPoint position);
    ~Snake() override = default;

    QRectF boundingRect() const override;
    void paint(QPainter*,
               const QStyleOptionGraphicsItem*,
               QWidget*) override;

    QPoint position() const;
    QPoint& position();

    void setDirection(Snake::Direction);
    Direction direction();

    ChunkSnake* addChunk();
    ChunkSnake* moveChunk();

public slots:
    void movement();

private:
    constexpr static int shift = 10;
    QPoint pos;
    enum Direction dir;

    ChunkSnake* head;
    ChunkSnake* tail;
    QList<ChunkSnake*> chunks;
    QHash<QPoint, bool> checkboard;
};

#endif // SNAKE_H
