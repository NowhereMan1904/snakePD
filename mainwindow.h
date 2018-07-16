#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "snake.h"
#include "fruit.h"
#include "menu.h"

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>
#include <QStackedLayout>
#include <QJsonObject>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow() override;

    void keyPressEvent(QKeyEvent *event) override;

    void readJSON(const QJsonObject &json);
    void writeJSON(QJsonObject &json) const;

public slots:
    void eatFruit();
    void movement();
    void loadFromJSON();
    void saveToJSON();
    void start();

signals:
    void speedChanged(QString);

private:
    void initializeHash();
    QPoint checkFruit();

    void endGame();
    void winGame();

    void showMenu();

    QGraphicsView* view;
    QGraphicsScene* scene;

    Menu* menu;

    QStackedLayout* stackedLayout;

    Snake* snake;
    Fruit* fruit;

    QTimer* timer;
    int time;

    QHash<QPoint, bool> checkboard;
};

#endif // MAINWINDOW_H
