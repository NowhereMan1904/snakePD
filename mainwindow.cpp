#include "mainwindow.h"
#include "snake.h"

#include <QLayout>
#include <QDebug>
#include <QInputEvent>
#include <QRandomGenerator>

bool operator<(const QPoint&, const QPoint&);

bool operator<(const QPoint& a, const QPoint& b) {
    if (a.y() < b.y())
        return true;
    if (a.y() > b.y())
        return false;
    if (a.x() < b.x())
        return true;
    return false;

}

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent},
      view {new QGraphicsView},
      scene {new QGraphicsScene},
      timer {new QTimer}
{
    setWindowTitle("SnakePorcoDio");
    setFixedSize(400,300);
    setFocus();

    scene->setBackgroundBrush(Qt::black);
    scene->setSceneRect(0,0,400,300);
    view->setScene(scene);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->setFrameShape(QGraphicsView::NoFrame);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMinimumSize(400,300);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(view);

    setLayout(layout);

    snake = new Snake{QPoint{(width()/2)+5, (height()/2)+5}};
    scene->addItem(snake->getHead());

    initializeHash();

    fruit = new Fruit{checkFruit()};
    scene->addItem(fruit);



    connect(timer, &QTimer::timeout,
            this,  &MainWindow::movement);
    connect(timer, &QTimer::timeout,
            this,  &MainWindow::checkPosition);

    timer->start(100);

}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (snake->canChangeDirection()) {
        switch (event->key()) {
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
    }
}

void MainWindow::checkPosition()
{
    if (snake->getHead()->position() == fruit->position()) {
        delete fruit;
        fruit = new Fruit{checkFruit()};
        scene->addItem(fruit);
        scene->addItem(snake->addChunk());
        checkboard[snake->getTail()->position()] = false;
    }
}

void MainWindow::movement()
{
    checkboard[snake->getTail()->position()] = true;
    snake->moveChunk();
    if (checkboard[snake->getHead()->position()] == false)
        endGame();
    else
        checkboard[snake->getHead()->position()] = false;
}

void MainWindow::endGame()
{
    if (checkboard[snake->getHead()->position()] == false) {
        timer->stop();
        auto text = new QGraphicsSimpleTextItem{"HAI PERSO PORCODDIO"};
        text->setPen(QPen{Qt::red});
        scene->addItem(text);
    }

}

void MainWindow::initializeHash()
{
    for (int i = 5; i<width(); i+=10) {
        for (int j = 5; j<height(); j+=10) {
            checkboard[QPoint{i,j}] = true;
        }
    }
    checkboard[snake->getHead()->position()] = false;
}

QPoint MainWindow::checkFruit()
{
    int x,y;
    do {
        x = QRandomGenerator::global()->bounded(40);
        y = QRandomGenerator::global()->bounded(30);
    } while (checkboard[QPoint{x*10+5,y*10+5}] == false);
    return QPoint{x*10+5,y*10+5};
}
