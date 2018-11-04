#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QHash>
#include <QObject>

class Fruit;
class MainWindow;
class SessionManager;
class SnakeController;

class QKeyEvent;
class QTimer;

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
    void exit();
    void keyHandler(QKeyEvent*);
    void readJSON();
    void writeJSON();
    void continueGame();
    void newGame();

signals:
    void lengthChanged(QString);
    void speedChanged (QString);
    void enableButtons(bool);

private:
    void initializeHash();
    QPoint checkFruit() const;

    void initGame();
    void winGame();

    int calculateSpeed() const;

    SessionManager*    sessionManager;
    SnakeController*   snakeController;
    Fruit*             fruit;
    MainWindow*        mainWindow;
    QTimer*            timer;
    QHash<QPoint,bool> checkboard;
    bool               isRunning;
};

#endif // GAMECONTROLLER_H
