#include "chunksnake.h"

#include <QPainter>

ChunkSnake::ChunkSnake(const QPoint& position)
    : pos{position}
{
}

QRectF ChunkSnake::boundingRect() const
{
    qreal penWidth = 10;
    return QRectF{pos.x() - penWidth/2, pos.y() - penWidth/2,
                  pos.x() + penWidth, pos.y() + penWidth};
}

void ChunkSnake::paint(QPainter* painter,
                       const QStyleOptionGraphicsItem*,
                       QWidget*)
{
    painter->setPen(QPen{color, 10});
    painter->drawPoint(pos);
}

QPoint ChunkSnake::getPosition() const
{
    return pos;
}

void ChunkSnake::setPosition(QPoint p)
{
    prepareGeometryChange();
    pos = p;
}

void ChunkSnake::setColor(QColor c)
{
    color = c;
}

void ChunkSnake::setX(int i)
{
    prepareGeometryChange();
    pos.setX(i);
}

void ChunkSnake::setY(int i)
{
    prepareGeometryChange();
    pos.setY(i);
}

void ChunkSnake::readJSON(const QJsonObject& json)
{
    pos.setX(json["pos"]["x"].toInt());
    pos.setY(json["pos"]["y"].toInt());

    color.setRed(json["color"]["red"].toInt());
    color.setGreen(json["color"]["green"].toInt());
    color.setBlue(json["color"]["blue"].toInt());
}

void ChunkSnake::writeJSON(QJsonObject& json) const
{
    QJsonObject posObject;
    posObject["x"] = pos.x();
    posObject["y"] = pos.y();

    QJsonObject colorObject;
    colorObject["red"] = color.red();
    colorObject["green"] = color.green();
    colorObject["blue"] = color.blue();

    json["pos"] = posObject;
    json["color"] = colorObject;
}
