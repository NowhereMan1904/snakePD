#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "snake.h"
#include "fruit.h"

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

public slots:
    void checkPosition();

private:
    constexpr static int shift = 10;
    QGraphicsView* view;
    QGraphicsScene* scene;

    Snake* snake;
    Fruit* fruit;

    QTimer* timer;
};

#endif // MAINWINDOW_H
