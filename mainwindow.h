#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "snake.h"

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

private:
    constexpr static int shift = 10;
    QGraphicsView* view;
    QGraphicsScene* scene;

    Snake* snake;
};

#endif // MAINWINDOW_H
