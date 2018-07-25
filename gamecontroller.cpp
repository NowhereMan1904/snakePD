#include "gamecontroller.h"

#include <QRandomGenerator>
#include <QKeyEvent>

GameController::GameController(QObject *parent)
    : QObject(parent),
      timer {new QTimer},
      time {100}
{
    snake = new Snake{QPoint{205, 155}};

    initializeHash();

    fruit = new Fruit{checkFruit()};

    connect(timer, &QTimer::timeout,
            this,  &GameController::movement);
    connect(timer, &QTimer::timeout,
            this,  &GameController::eatFruit);

    mainWindow = new MainWindow(this, snake);

    timer->start(time);
}

SessionManager* GameController::getSessionManager() const
{
    return sessionManager;
}

void GameController::exit()
{
    QApplication::quit();
}

void GameController::initializeHash()
{
    for (int i = 5; i<400; i+=10)
        for (int j = 5; j<300; j+=10)
            checkboard[QPoint{i,j}] = true;

    checkboard[snake->getHead()->position()] = false;
}

QPoint GameController::checkFruit()
{
    int x,y;
    do {
        x = QRandomGenerator::global()->bounded(40);
        y = QRandomGenerator::global()->bounded(30);
    } while (checkboard[QPoint{x*10+5,y*10+5}] == false);
    return QPoint{x*10+5,y*10+5};
}

void GameController::endGame()
{
    timer->stop();
    snake->hide();
    fruit->hide();
    auto text = new QGraphicsSimpleTextItem{"HAI PERSO PORCODDIO"};
    text->setPen(QPen{Qt::red});
    text->setPos(200 - text->boundingRect().center().x(),
                 150 - text->boundingRect().center().y());
    mainWindow->getScene()->addItem(text);
}

void GameController::winGame()
{
    timer->stop();
    auto text = new QGraphicsSimpleTextItem{"HAI VINTO PORCAMADONNA"};
    text->setPen(QPen{Qt::green});
    mainWindow->getScene()->addItem(text);
}

Fruit* GameController::getFruit() const
{
    return fruit;
}

bool GameController::event(QEvent* e)
{
    if (snakeController->canChangeDirection() &&
            e->type() == QEvent::KeyPress) {
        auto ke = static_cast<QKeyEvent*>(e);
        switch (ke->key()) {
            case Qt::Key_Left:
                if (snake->direction() != Snake::Direction::Right)
                    snake->setDirection(Snake::Direction::Left);
                break;
            case Qt::Key_Right:
                if (snake->direction() != Snake::Direction::Left)
                    snake->setDirection(Snake::Direction::Right);
                break;
            case Qt::Key_Up:
                if (snake->direction() != Snake::Direction::Down)
                    snake->setDirection(Snake::Direction::Up);
                break;
            case Qt::Key_Down:
                if (snake->direction() != Snake::Direction::Up)
                    snake->setDirection(Snake::Direction::Down);
                break;
            default:
                break;
        }
        return true;
    }
}

void GameController::eatFruit()
{
    if (snake->getHead()->position() == fruit->position()) {
        snake->changeColor(fruit->getColor());
        fruit->move(checkFruit());
        mainWindow->getScene()->addItem(snake->addChunk());
        checkboard[snake->getTail()->position()] = false;

        if (snake->getLength() == 40*30)
            winGame();

        if (snake->getLength() % 5 == 0 && time>=5) {
            time -= time/10;
            timer->start(time);

//            emit speedChanged(QString::number(1000/time));
        }
    }
}

void GameController::movement()
{
    checkboard[snake->getTail()->position()] = true;
    snakeController->moveChunk();
    if (checkboard[snake->getHead()->position()] == false)
        endGame();
    else
        checkboard[snake->getHead()->position()] = false;
}

void GameController::start()
{
    mainWindow->closeMenu();
    timer->start();
}
