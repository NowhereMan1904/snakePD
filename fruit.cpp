#include "fruit.h"

#include <QJsonArray>
#include <QPainter>
#include <QRandomGenerator>

Fruit::Fruit(QPoint p)
{
    move(p);
}

QRectF Fruit::boundingRect() const
{
    qreal penWidth = 12;
    return QRectF{pos.x() - penWidth/2, pos.y() - penWidth/2,
                  pos.x() + penWidth, pos.y() + penWidth};
}

void Fruit::paint(QPainter* painter,
                  const QStyleOptionGraphicsItem*,
                  QWidget*)
{
    painter->setPen(QPen{Qt::NoPen});
    painter->setBrush(QBrush{color});
    painter->drawEllipse(pos, 6, 6);
}

QPoint Fruit::position() const
{
    return pos;
}

QColor Fruit::getColor() const
{
    return color;
}

void Fruit::readJSON(const QJsonObject& json)
{
    pos.setX(json["pos"]["x"].toInt());
    pos.setY(json["pos"]["y"].toInt());

    color.setRed(json["color"]["red"].toInt());
    color.setGreen(json["color"]["green"].toInt());
    color.setBlue(json["color"]["blue"].toInt());
}

void Fruit::writeJSON(QJsonObject& json) const
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

void Fruit::move(const QPoint& p)
{
    prepareGeometryChange();

    pos = p;

    auto r = QRandomGenerator::global()->bounded(100,256);
    auto g = QRandomGenerator::global()->bounded(100,256);
    auto b = QRandomGenerator::global()->bounded(100,256);
    color = QColor{r,g,b};
}
