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
    ~MainWindow() override = default;

    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void eatFruit();
    void movement();

signals:
    void speedChanged(QString);

private:
    void initializeHash();
    QPoint checkFruit();

    void endGame();
    void winGame();

    QGraphicsView* view;
    QGraphicsScene* scene;

    Snake* snake;
    Fruit* fruit;

    QTimer* timer;
    int time;

    QHash<QPoint, bool> checkboard;
};

#endif // MAINWINDOW_H
