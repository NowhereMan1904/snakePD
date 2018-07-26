#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include "chunksnake.h"
#include "snake.h"
#include <QObject>

class SnakeController
{
public:
    explicit SnakeController();
    ~SnakeController();

    void changeDirection(QKeyEvent*);

    Snake* getSnake() const;

    void moveChunk();

private:
    bool canChangeDirection();

    Snake* snake;
    bool enable;
    constexpr static int shift = 10;
};

#endif // SNAKECONTROLLER_H
