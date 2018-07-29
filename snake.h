#ifndef SNAKE_H
#define SNAKE_H

#include "chunksnake.h"

#include <QObject>

class Snake : public QObject
{
    Q_OBJECT

public:
    enum class Direction { Up, Down, Left, Right, Stop };

    Snake(QPoint);
    ~Snake() override = default;

    void      setDirection(Direction);
    Direction getDirection() const;

    void   setCurrentColor(QColor);
    QColor getCurrentColor() const;

    ChunkSnake*        getHead()   const;
    ChunkSnake*        getTail()   const;
    int                getLength() const;
    QList<ChunkSnake*> getChunks() const;   // do NOT use this function to
                                            // modify the chunk list

    void hide() const;
    void cycle();
    void readJSON (const QJsonObject&);
    void writeJSON(QJsonObject&) const;

public slots:
    ChunkSnake* addChunk();

private:
    enum Direction     dir;
    QColor             currentColor;
    QList<ChunkSnake*> chunks;
};

#endif // SNAKE_H
