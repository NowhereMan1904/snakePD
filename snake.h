#ifndef SNAKE_H
#define SNAKE_H

#include "chunksnake.h"

class Snake
{
public:
    enum class Direction { Up, Down, Left, Right, Stop };

    Snake(QPoint);

    void      setDirection(Direction);
    Direction getDirection() const;

    void   setCurrentColor(QColor);
    QColor getCurrentColor() const;

    ChunkSnake*        getHead()   const;
    ChunkSnake*        getTail()   const;
    int                getLength() const;
    QList<ChunkSnake*> getChunks() const;   // do NOT use this function to
                                            // modify the chunk list

    ChunkSnake* addChunk();
    void hide() const;
    void cycle();
    void readJSON (const QJsonObject&);
    void writeJSON(QJsonObject&) const;

private:
    enum Direction     dir;
    QColor             currentColor;
    QList<ChunkSnake*> chunks;
};

#endif // SNAKE_H
