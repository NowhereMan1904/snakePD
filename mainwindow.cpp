#include "mainwindow.h"

#include <QLayout>
#include <QInputEvent>
#include <QRandomGenerator>
#include <QLabel>
#include <QJsonDocument>

inline uint qHash(QPoint key, uint seed)
{
    return qHash(qMakePair(key.x(), key.y()), seed);
}

MainWindow::MainWindow(GameController* gameController,
                       Snake* snake)
    : QWidget{nullptr},
      view {new QGraphicsView},
      scene {new QGraphicsScene},
      menu {new Menu{gameController}},
      stackedLayout {new QStackedLayout}
{
    setFocusPolicy(Qt::StrongFocus);
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
//    auto speedLabel = new QLabel{QString::number(1000/time)};
//    speedLabel->setStyleSheet("font-weight: bold");
    auto speedText = new QLabel{"SPEED:"};
    speedText->setStyleSheet("font-weight: bold");
    labelLayout->addWidget(speedText);
//    labelLayout->addWidget(speedLabel);

    // Stacked Layout
    stackedLayout->addWidget(view);
    stackedLayout->addWidget(menu);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    //layout->addWidget(view);
    layout->addLayout(stackedLayout);
    layout->addWidget(labelWidget);

    setLayout(layout);

    scene->addItem(snake->getHead());


    scene->addItem(gameController->getFruit());

    connect(snake, &Snake::lengthChanged,
            lengthLabel, &QLabel::setText);
//    connect(this, &MainWindow::speedChanged,
//            speedLabel, &QLabel::setText);

}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) {
        showMenu();
        event->accept();
    }
}

void MainWindow::readJSON(const QJsonObject& json)
{
    QJsonObject fruitObject = json["fruit"].toObject();
    fruit->readJSON(fruitObject);

    QJsonObject snakeObject = json["snake"].toObject();
    snake->readJSON(snakeObject);

    time = json["time"].toInt();

    checkboard.clear();
    for (int i = 5; i<width(); i+=10)
        for (int j = 5; j<height(); j+=10)
            checkboard[QPoint{i,j}] = true;

    auto chunks = snake->getChunks();
    for (auto c : chunks) {
        scene->addItem(c);
        checkboard[c->position()] = false;
    }
}

void MainWindow::loadFromJSON()
{
    QFile loadFile("save.Json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    readJSON(loadDoc.object());
}

void MainWindow::writeJSON(QJsonObject &json) const
{
    QJsonObject fruitObject;
    fruit->writeJSON(fruitObject);
    json["fruit"] = fruitObject;

    QJsonObject snakeObject;
    snake->writeJSON(snakeObject);
    json["snake"] = snakeObject;

    json["time"] = time;
}

void MainWindow::saveToJSON()
{
    QFile saveFile("save.Json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonObject gameObject;
    writeJSON(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());
}

void MainWindow::showMenu()
{
    timer->stop();
    stackedLayout->setCurrentWidget(menu);
}

QGraphicsScene* MainWindow::getScene() const
{
    return scene;
}

void MainWindow::closeMenu() const
{
    stackedLayout->setCurrentWidget(view);
}
