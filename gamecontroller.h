#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "fruit.h"
#include "mainwindow.h"
#include "sessionmanager.h"
#include "snakecontroller.h"

#include <QObject>
#include <QTimer>

class GameController : public QObject
{
    Q_OBJECT

public:
    explicit GameController(QObject *parent = nullptr);
    ~GameController() override;

    SessionManager* getSessionManager() const;
    Fruit*          getFruit()          const;

public slots:
    void eatFruit();
    void movement();
    void start();
    void exit();
    void keyHandler(QKeyEvent*);
    void readJSON();
    void writeJSON();
    void continueGame();
    void newGame();

signals:
    void lengthChanged(QString);
    void speedChanged (QString);

private:
    void initializeHash();
    QPoint checkFruit() const;

    void initGame();
    void endGame();
    void winGame();

    int calculateSpeed() const;

    void reset();

    SessionManager*    sessionManager;
    SnakeController*   snakeController;
    Fruit*             fruit;
    MainWindow*        mainWindow;
    QTimer*            timer;
    QHash<QPoint,bool> checkboard;
};

#endif // GAMECONTROLLER_H
