#include "mainwindow.h"

#include "gamecontroller.h"

#include <QLabel>

MainWindow::MainWindow(GameController* gameController,
                       Snake* snake)
    : QWidget{nullptr},
      view {new QGraphicsView},
      scene {new QGraphicsScene},
      menu {new Menu{gameController}},
      stackedLayout {new QStackedLayout}
{
    // Window
    setWindowTitle("SnakePorcoDio");
    setFocus();

    // View
    scene->setBackgroundBrush(Qt::black);
    scene->setSceneRect(0,0,400,300);
    view->setScene(scene);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->setFrameShape(QGraphicsView::NoFrame);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(400,300);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setFocusPolicy(Qt::NoFocus);

    // Status bar
    auto labelWidget = new QWidget;
    auto labelLayout = new QHBoxLayout;
    auto lengthLabel = new QLabel{"1"};
    lengthLabel->setStyleSheet("font-weight: bold");
    auto lengthText  = new QLabel{"SCORE:"};
    lengthText->setStyleSheet("font-weight: bold");
    labelLayout->addWidget(lengthText);
    labelLayout->addWidget(lengthLabel);
    labelWidget->setLayout(labelLayout);
    auto speedLabel = new QLabel{QString::number(10)};
    speedLabel->setStyleSheet("font-weight: bold");
    auto speedText = new QLabel{"SPEED:"};
    speedText->setStyleSheet("font-weight: bold");
    labelLayout->addWidget(speedText);
    labelLayout->addWidget(speedLabel);

    // Stacked Layout
    stackedLayout->addWidget(view);
    stackedLayout->addWidget(menu);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addLayout(stackedLayout);
    layout->addWidget(labelWidget);

    setLayout(layout);

    scene->addItem(snake->getHead());
    scene->addItem(gameController->getFruit());

    connect(gameController, &GameController::lengthChanged,
            lengthLabel, &QLabel::setText);
    connect(gameController, &GameController::speedChanged,
            speedLabel, &QLabel::setText);
    connect(this, &MainWindow::keyPressed,
            gameController, &GameController::keyHandler);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    emit keyPressed(event);
}

QGraphicsScene* MainWindow::getScene() const
{
    return scene;
}

void MainWindow::showMenu()
{
    stackedLayout->setCurrentWidget(menu);
    menu->setFocus();
}

void MainWindow::closeMenu()
{
    stackedLayout->setCurrentWidget(view);
    setFocus();
}
