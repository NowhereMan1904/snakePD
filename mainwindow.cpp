#include "mainwindow.h"
#include "snake.h"

#include <QLayout>
#include <QDebug>
#include <QInputEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent},
      view {new QGraphicsView},
      scene {new QGraphicsScene}
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
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        if (snake->getDirection() != Snake::direction::Right)
            snake->setDirection(Snake::direction::Left);
        break;
    case Qt::Key_Right:
        if (snake->getDirection() != Snake::direction::Left)
            snake->setDirection(Snake::direction::Right);
        break;
    case Qt::Key_Up:
        if (snake->getDirection() != Snake::direction::Down)
            snake->setDirection(Snake::direction::Up);
        break;
    case Qt::Key_Down:
        if (snake->getDirection() != Snake::direction::Up)
            snake->setDirection(Snake::direction::Down);
        break;
    default:
        break;
    }
}
