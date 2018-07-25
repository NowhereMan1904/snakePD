#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "sessionmanager.h"
#include "snakecontroller.h"
#include "mainwindow.h"
#include "snake.h"
#include "fruit.h"

#include <QObject>
#include <QTimer>

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr);

    SessionManager* getSessionManager() const;

    Fruit* getFruit() const;

    bool event(QEvent*) override;

signals:

public slots:
    void eatFruit();
    void movement();
    void start();
    void exit();

private:
    void initializeHash();
    QPoint checkFruit();

    void endGame();
    void winGame();

    SessionManager* sessionManager;
    SnakeController* snakeController;
    Snake* snake;
    Fruit* fruit;
    MainWindow* mainWindow;

    QTimer* timer;
    int time;

    QHash<QPoint, bool> checkboard;
};

#endif // GAMECONTROLLER_H
