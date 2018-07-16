#include "snake.h"

#include <QJsonArray>

Snake::Snake(QPoint position)
    : dir {Direction::Stop},
      enable {true},
      currentColor {Qt::white}
{
    chunks << new ChunkSnake{position};
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

void Snake::changeColor(QColor color)
{
    currentColor = color;
}

int Snake::getLength() const
{
    return chunks.size();
}

QList<ChunkSnake*> Snake::getChunks() const
{
    return chunks;
}

void Snake::hide()
{
    for (auto c : chunks)
        c->hide();
}

void Snake::readJSON(const QJsonObject& json)
{
    dir = static_cast<Direction>(json["direction"].toInt());
    enable = json["enable"].toBool();
    currentColor.setRed(json["currentColor"]["red"].toInt());
    currentColor.setGreen(json["currentColor"]["green"].toInt());
    currentColor.setBlue(json["currentColor"]["blue"].toInt());

    QJsonArray chunkArray = json["chunks"].toArray();
    qDeleteAll(chunks);
    chunks.clear();
    for (int i = 0; i < chunkArray.size(); ++i) {
        QJsonObject chunkObject = chunkArray[i].toObject();
        auto chunk = new ChunkSnake;
        chunk->readJSON(chunkObject);
        chunks.append(chunk);
    }
}

void Snake::writeJSON(QJsonObject& json) const
{
    QJsonObject colorObject;
    colorObject["red"] = currentColor.red();
    colorObject["green"] = currentColor.green();
    colorObject["blue"] = currentColor.blue();

    QJsonArray chunkArray;
    for (auto c : chunks) {
        QJsonObject chunkObject;
        c->writeJSON(chunkObject);
        chunkArray.append(chunkObject);
    }

    json["direction"] = static_cast<int>(dir);
    json["enable"] = enable;
    json["currentColor"] = colorObject;
    json["chunks"] = chunkArray;
}

ChunkSnake* Snake::addChunk()
{
    auto chunk = new ChunkSnake{chunks.back()->position()};
    chunk->setColor(Qt::transparent);
    chunks << chunk;

    emit lengthChanged(QString::number(chunks.size()));
    return chunk;
}

ChunkSnake* Snake::moveChunk()
{
    enable = true;

    auto p = chunks.back();

    switch (dir) {
    case Direction::Up:
        p->position() = QPoint{
                        chunks.front()->position().rx(),
                        chunks.front()->position().ry() - shift};
        break;
    case Direction::Down:
        p->position() = QPoint{
                        chunks.front()->position().rx(),
                        chunks.front()->position().ry() + shift};
        break;
    case Direction::Left:
        p->position() = QPoint{
                        chunks.front()->position().rx() - shift,
                        chunks.front()->position().ry()};
        break;
    case Direction::Right:
        p->position() = QPoint{
                        chunks.front()->position().rx() + shift,
                        chunks.front()->position().ry()};
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

    p->setColor(currentColor);

    chunks.removeLast();
    chunks.push_front(p);

    return p;
}
