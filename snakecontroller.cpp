#include "snakecontroller.h"

SnakeController::SnakeController(Snake* s)
    : QObject(nullptr),
      snake {s},
      enable {true}
{

}

bool SnakeController::canChangeDirection()
{
    if (enable) {
        enable = false;
        return true;
    }
    return false;
}

ChunkSnake* SnakeController::moveChunk()
{
    enable = true;

    auto p = snake->getTail();

    switch (snake->direction()) {
    case Snake::Direction::Up:
        p->position() = QPoint{
                        snake->getHead()->position().x(),
                        snake->getHead()->position().y() - shift};
        break;
    case Snake::Direction::Down:
        p->position() = QPoint{
                        snake->getHead()->position().x(),
                        snake->getHead()->position().y() + shift};
        break;
    case Snake::Direction::Left:
        p->position() = QPoint{
                        snake->getHead()->position().x() - shift,
                        snake->getHead()->position().y()};
        break;
    case Snake::Direction::Right:
        p->position() = QPoint{
                        snake->getHead()->position().x() + shift,
                        snake->getHead()->position().y()};
        break;
    default:
        break;
    }

    p->position().rx() =
            p->position().rx()<5 ?
                400-5 :
                p->position().rx()%400;
    p->position().ry() =
            p->position().ry()<5 ?
                300-5 :
                p->position().ry()%300;

    p->setColor(snake->getCurrentColor());

    snake->getChunks().removeLast();
    snake->getChunks().push_front(p);

    return p;
}
