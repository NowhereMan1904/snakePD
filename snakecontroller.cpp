#include "snakecontroller.h"

SnakeController::SnakeController()
    : enable {true}
{
    snake = new Snake{QPoint{205, 155}};
}

SnakeController::~SnakeController()
{
    delete snake;
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
                    if (snake->getDirection() != Snake::Direction::Right)
                        snake->setDirection(Snake::Direction::Left);
                    break;
                case Qt::Key_Right:
                    if (snake->getDirection() != Snake::Direction::Left)
                        snake->setDirection(Snake::Direction::Right);
                    break;
                case Qt::Key_Up:
                    if (snake->getDirection() != Snake::Direction::Down)
                        snake->setDirection(Snake::Direction::Up);
                    break;
                case Qt::Key_Down:
                    if (snake->getDirection() != Snake::Direction::Up)
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

    switch (snake->getDirection()) {
    case Snake::Direction::Up:
        p->setPosition(QPoint{snake->getHead()->getPosition().x(),
                              snake->getHead()->getPosition().y() - shift});
        break;
    case Snake::Direction::Down:
        p->setPosition(QPoint{snake->getHead()->getPosition().x(),
                              snake->getHead()->getPosition().y() + shift});
        break;
    case Snake::Direction::Left:
        p->setPosition(QPoint{snake->getHead()->getPosition().x() - shift,
                              snake->getHead()->getPosition().y()});
        break;
    case Snake::Direction::Right:
        p->setPosition(QPoint{snake->getHead()->getPosition().x() + shift,
                              snake->getHead()->getPosition().y()});
        break;
    default:
        break;
    }

    p->setX(p->getPosition().x()<5 ?
                400-5 :
                p->getPosition().x()%400);
    p->setY(p->getPosition().y()<5 ?
                300-5 :
                p->getPosition().y()%300);

    p->setColor(snake->getCurrentColor());

    snake->cycle();
}

bool SnakeController::canChangeDirection()
{
    if (enable) {
        enable = false;
        return true;
    }
    return false;
}
