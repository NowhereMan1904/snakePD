#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include "snake.h"

#include <QKeyEvent>

class SnakeController
{
public:
    explicit SnakeController();
    ~SnakeController();

    Snake* getSnake() const;
    void changeDirection(int);
    void moveChunk();

private:
    bool canChangeDirection();

    Snake* snake;
    bool   enable;

    constexpr static int shift = 10;
};

#endif // SNAKECONTROLLER_H
