#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include "chunksnake.h"
#include "snake.h"
#include <QObject>

class SnakeController : public QObject
{
    Q_OBJECT
public:
    explicit SnakeController(Snake*);

    bool canChangeDirection();

signals:

public slots:
    ChunkSnake* moveChunk();

private:
    Snake* snake;
    bool enable;
    constexpr static int shift = 10;
};

#endif // SNAKECONTROLLER_H
