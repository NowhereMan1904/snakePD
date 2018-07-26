#include "snakecontroller.h"

#include <QKeyEvent>

SnakeController::SnakeController()
    : enable {true}
{
    snake = new Snake{QPoint{205, 155}};
}

bool SnakeController::canChangeDirection()
{
    if (enable) {
        enable = false;
        return true;
    }
    return false;
}

Snake* SnakeController::getSnake() const
{
    return snake;
}

void SnakeController::changeDirection(QKeyEvent* e)
{
    if (canChangeDirection()) {
            switch (e->key()) {
                case Qt::Key_Left:
                    if (snake->direction() != Snake::Direction::Right)
                        snake->setDirection(Snake::Direction::Left);
                    break;
                case Qt::Key_Right:
                    if (snake->direction() != Snake::Direction::Left)
                        snake->setDirection(Snake::Direction::Right);
                    break;
                case Qt::Key_Up:
                    if (snake->direction() != Snake::Direction::Down)
                        snake->setDirection(Snake::Direction::Up);
                    break;
                case Qt::Key_Down:
                    if (snake->direction() != Snake::Direction::Up)
                        snake->setDirection(Snake::Direction::Down);
                    break;
                default:
                    break;
            }
        }
}

void SnakeController::moveChunk()
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
            p->position().x()<5 ?
                400-5 :
                p->position().x()%400;
    p->position().ry() =
            p->position().y()<5 ?
                300-5 :
                p->position().y()%300;

    p->setColor(snake->getCurrentColor());

    snake->getChunks().removeLast();
    snake->getChunks().push_front(p);
}
