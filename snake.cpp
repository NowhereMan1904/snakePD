#include "snake.h"

#include <QDebug>
#include <QInputEvent>
#include <QPainter>

Snake::Snake(QPoint position)
    : dir {Direction::Left},
      enable {true}
{
    auto chunk = new ChunkSnake{position};
    chunks << chunk;
}

void Snake::setDirection(Snake::Direction direction)
{
    dir = direction;
}

Snake::Direction Snake::direction()
{
    return dir;
}

ChunkSnake* Snake::getHead()
{
    return chunks.front();
}

bool Snake::canChangeDirection()
{
    if (enable) {
        enable = false;
        return !enable;
    }
    return enable;
}

ChunkSnake* Snake::addChunk()
{
    auto chunk = new ChunkSnake{chunks.back()->position()};
    chunks.push_back(chunk);

    return chunk;
}

ChunkSnake* Snake::moveChunk()
{
    auto p = chunks.back();

    switch (dir) {
    case Direction::Up:
        p->position().ry() =
                chunks.front()->position().ry() - shift;
        break;
    case Direction::Down:
        p->position().ry() =
                chunks.front()->position().ry() + shift;
        break;
    case Direction::Left:
        p->position().rx() =
                chunks.front()->position().rx() - shift;
        break;
    case Direction::Right:
        p->position().rx() =
                chunks.front()->position().rx() + shift;
        break;
    default:
        break;
    }

    p->position().rx() =
            p->position().rx()<=0 ?
                400-10 :
                p->position().rx()%400;
    p->position().ry() =
            p->position().ry()<=0 ?
                300-10 :
                p->position().ry()%300;

    chunks.removeLast();
    chunks.push_front(p);

    return p;
}

void Snake::movement()
{
    enable = true;
    moveChunk();
}
