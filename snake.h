#ifndef SNAKE_H
#define SNAKE_H

#include <QTimer>
#include <QGraphicsObject>
#include <QList>
#include <QHash>

#include "chunksnake.h"
#include "fruit.h"

class Snake : public QObject
{
    Q_OBJECT

public:
    enum class Direction { Up, Down, Left, Right, Stop };

    Snake(QPoint position);
    ~Snake() override = default;

    void setDirection(Snake::Direction);
    Direction direction();

    ChunkSnake* getHead();
    ChunkSnake* getTail();

    bool canChangeDirection();

    void changeColor(Fruit*);

    int getLength() const;

public slots:
    ChunkSnake* addChunk();
    ChunkSnake* moveChunk();

signals:
    void lenghtChanged(QString);

private:
    constexpr static int shift = 10;
    enum Direction dir;
    bool enable;
    QColor currentColor;

    QList<ChunkSnake*> chunks;
};

#endif // SNAKE_H
