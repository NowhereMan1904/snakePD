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
    ~GameController() override;

    SessionManager* getSessionManager() const;

    Fruit* getFruit() const;

public slots:
    void eatFruit();
    void movement();
    void start();
    void exit();
    void keyHandler(QKeyEvent*);
    void readJSON();
    void writeJSON();

private:
    void initializeHash();
    QPoint checkFruit();

    void endGame();
    void winGame();

    SessionManager* sessionManager;
    SnakeController* snakeController;
    Fruit* fruit;
    MainWindow* mainWindow;

    QTimer* timer;
    int time;

    QHash<QPoint, bool> checkboard;
};

#endif // GAMECONTROLLER_H
