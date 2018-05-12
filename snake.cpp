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

ChunkSnake* Snake::getTail()
{
    return chunks.back();
}

bool Snake::canChangeDirection()
{
    if (enable) {
        enable = false;
        return true;
    }
    return false;
}

void Snake::changeColor(Fruit* fruit)
{
    ChunkSnake::color = fruit->getColor();
}

ChunkSnake* Snake::addChunk()
{
    auto chunk = new ChunkSnake{chunks.back()->position()};
    chunks.push_back(chunk);

    emit lenghtChanged(QString::number(chunks.size()));
    return chunk;
}

ChunkSnake* Snake::moveChunk()
{
    enable = true;

    auto p = chunks.back();

    switch (dir) {
    case Direction::Up:
        p->position().ry() =
                chunks.front()->position().ry() - shift;
        p->position().rx() =
                chunks.front()->position().rx();
        break;
    case Direction::Down:
        p->position().ry() =
                chunks.front()->position().ry() + shift;
        p->position().rx() =
                chunks.front()->position().rx();
        break;
    case Direction::Left:
        p->position().rx() =
                chunks.front()->position().rx() - shift;
        p->position().ry() =
                chunks.front()->position().ry();
        break;
    case Direction::Right:
        p->position().rx() =
                chunks.front()->position().rx() + shift;
        p->position().ry() =
                chunks.front()->position().ry();
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

    chunks.removeLast();
    chunks.push_front(p);

    return p;
}
