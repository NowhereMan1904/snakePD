#include "gamecontroller.h"

#include "chunksnake.h"
#include "fruit.h"
#include "mainwindow.h"
#include "sessionmanager.h"
#include "snake.h"
#include "snakecontroller.h"


#include <QApplication>
#include <QGraphicsScene>
#include <QJsonObject>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTimer>

inline uint qHash(QPoint key, uint seed)
{
    return qHash(qMakePair(key.x(), key.y()), seed);
}

GameController::GameController(QObject *parent)
    : QObject(parent),
      sessionManager {new SessionManager},
      mainWindow {new MainWindow(this)},
      timer {new QTimer{this}},
      isRunning {false}
{
    initGame();

    connect(timer, &QTimer::timeout,
            this,  &GameController::movement);
    connect(timer, &QTimer::timeout,
            this,  &GameController::eatFruit);

    mainWindow->show();
}

GameController::~GameController()
{
    delete sessionManager;
    delete snakeController;
}

SessionManager* GameController::getSessionManager() const
{
    return sessionManager;
}

Fruit* GameController::getFruit() const
{
    return fruit;
}

void GameController::eatFruit()
{
    auto snake = snakeController->getSnake();
    if (snake->getHead()->getPosition() == fruit->getPosition()) {
        snake->setCurrentColor(fruit->getColor());
        fruit->move(checkFruit());
        mainWindow->getScene()->addItem(snake->addChunk());

        // not really sure about next line
        checkboard.insert(snake->getTail()->getPosition(),
                         false);

        if (snake->getLength() == 40*30)
            winGame();

        if (snake->getLength() % 5 == 0) {
            int s = calculateSpeed();
            timer->start(s);

            emit speedChanged(QString::number(1000/s));
        }

        emit lengthChanged(QString::number(snake->getLength()));
    }
}

void GameController::movement()
{
    auto snake = snakeController->getSnake();
    checkboard.insert(snake->getTail()->getPosition(),
                      true);

    snakeController->moveChunk();

    if (checkboard.value(snake->getHead()->getPosition()) == false) {
        isRunning = false;
        mainWindow->showLoose();
        emit enableButtons(false);
    }
    else {
        checkboard.insert(snake->getHead()->getPosition(),
                          false);
    }
}

void GameController::exit()
{
    QApplication::quit();
}

void GameController::keyHandler(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Space) {
        timer->stop();
        mainWindow->showMenu();
    } else
        snakeController->changeDirection(e);
}

void GameController::readJSON()
{
    QJsonObject json;

    if (sessionManager->loadFromJSON(json)) {
        QJsonObject fruitObject = json["fruit"].toObject();
        fruit->readJSON(fruitObject);

        QJsonObject snakeObject = json["snake"].toObject();
        snakeController->getSnake()->readJSON(snakeObject);

        checkboard.clear();
        checkboard.reserve(40*30);
        for (int i = 5; i<400; i+=10)
            for (int j = 5; j<300; j+=10)
                checkboard.insert(QPoint{i,j},
                                  true);

        for (auto c : snakeController->getSnake()->getChunks()) {
            mainWindow->getScene()->addItem(c);
            checkboard.insert(c->getPosition(),
                              false);
        }
        isRunning = true;
        emit enableButtons(true);
    }
}

void GameController::writeJSON()
{
    if (isRunning) {
        QJsonObject json;

        QJsonObject fruitObject;
        fruit->writeJSON(fruitObject);
        json["fruit"] = fruitObject;

        QJsonObject snakeObject;
        snakeController->getSnake()->writeJSON(snakeObject);
        json["snake"] = snakeObject;

        sessionManager->saveToJSON(json);
    }
}

void GameController::continueGame()
{
    if (isRunning) {
        mainWindow->showView();
        timer->start(calculateSpeed());
    }
}

void GameController::newGame()
{
    delete snakeController;
    delete fruit;
    emit enableButtons(true);
    isRunning = true;
    initGame();
    continueGame();
}

void GameController::initializeHash()
{
    checkboard.reserve(1300);
    for (int i = 5; i<400; i+=10)
        for (int j = 5; j<300; j+=10)
            checkboard.insert(QPoint{i,j},
                              true);

    checkboard.insert(snakeController->getSnake()->getHead()->getPosition(),
                      false);
}

QPoint GameController::checkFruit() const
{
    int x,y;
    do {
        x = QRandomGenerator::global()->bounded(40);
        y = QRandomGenerator::global()->bounded(30);
    } while (checkboard.value(QPoint{x*10+5,y*10+5}) == false);
    return QPoint{x*10+5,y*10+5};
}

void GameController::initGame()
{
    snakeController = new SnakeController;
    initializeHash();
    fruit = new Fruit(checkFruit());
    emit lengthChanged(QString::number(snakeController->
                                       getSnake()->
                                       getLength()));
    emit speedChanged(QString::number(1000/calculateSpeed()));
    mainWindow->getScene()->addItem(
                snakeController->getSnake()->getHead());
    mainWindow->getScene()->addItem(fruit);
}

void GameController::winGame()
{
    timer->stop();
    auto text = new QGraphicsSimpleTextItem{"HAI VINTO PORCAMADONNA"};
    text->setPen(QPen{Qt::green});
    mainWindow->getScene()->addItem(text);
}

int GameController::calculateSpeed() const
{
    auto l = snakeController->getSnake()->getLength();
    auto s = 100;

    for (int i = l/5; i>0; --i)
        s -= s/10;

    return s;
}
