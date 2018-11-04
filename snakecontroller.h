#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

class Snake;

class QKeyEvent;

class SnakeController
{
public:
    explicit SnakeController();
    ~SnakeController();

    Snake* getSnake() const;
    void changeDirection(QKeyEvent*);
    void moveChunk();
    void reset();

private:
    bool canChangeDirection();

    Snake* snake;
    bool   enable;

    constexpr static int shift = 10;
};

#endif // SNAKECONTROLLER_H
