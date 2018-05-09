#include "mainwindow.h"
#include "snake.h"

#include <QLayout>
#include <QDebug>
#include <QInputEvent>

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

    snake = new Snake{QPoint{width()/2, height()/2}};
    scene->addItem(snake);

    fruit = new Fruit{};
    scene->addItem(fruit);

    connect(timer, &QTimer::timeout,
            snake, &Snake::movement);
    connect(timer, &QTimer::timeout,
            this,  &MainWindow::checkPosition);

    timer->start(100);

}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
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

void MainWindow::checkPosition()
{
    if (snake->position() == fruit->position()) {
        delete fruit;
        fruit = new Fruit{};
        scene->addItem(fruit);
    }
}
