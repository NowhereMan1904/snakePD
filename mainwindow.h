#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "snake.h"
#include "fruit.h"

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>

#include <map>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

    void endGame();

public slots:
    void checkPosition();
    void movement();

private:
    void initializeHash();
    QPoint checkFruit();

    constexpr static int shift = 10;
    QGraphicsView* view;
    QGraphicsScene* scene;

    Snake* snake;
    Fruit* fruit;

    QTimer* timer;

    std::map<QPoint, bool> checkboard;
};

#endif // MAINWINDOW_H
