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

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent},
      view {new QGraphicsView},
      scene {new QGraphicsScene},
      menu {new Menu},
      stackedLayout {new QStackedLayout},
      timer {new QTimer},
      time {100}
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
    auto speedLabel = new QLabel{QString::number(1000/time)};
    speedLabel->setStyleSheet("font-weight: bold");
    auto speedText = new QLabel{"SPEED:"};
    speedText->setStyleSheet("font-weight: bold");
    labelLayout->addWidget(speedText);
    labelLayout->addWidget(speedLabel);

    // Stacked Layout
    stackedLayout->addWidget(view);
    stackedLayout->addWidget(menu);
    connect(menu, &Menu::start,
            this, &MainWindow::start);
    connect(menu, &Menu::load,
            this, &MainWindow::loadFromJSON);
    connect(menu, &Menu::save,
            this, &MainWindow::saveToJSON);


    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    //layout->addWidget(view);
    layout->addLayout(stackedLayout);
    layout->addWidget(labelWidget);

    setLayout(layout);

    snake = new Snake{QPoint{(view->width()/2)+5,
                             (view->height()/2)+5}};
    scene->addItem(snake->getHead());

    initializeHash();

    fruit = new Fruit{checkFruit()};
    scene->addItem(fruit);

    connect(snake, &Snake::lengthChanged,
            lengthLabel, &QLabel::setText);
    connect(this, &MainWindow::speedChanged,
            speedLabel, &QLabel::setText);
    connect(timer, &QTimer::timeout,
            this,  &MainWindow::movement);
    connect(timer, &QTimer::timeout,
            this,  &MainWindow::eatFruit);

    timer->start(time);
}

MainWindow::~MainWindow()
{
    delete snake;
    delete timer;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) {
        showMenu();
    }
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

void MainWindow::eatFruit()
{
    if (snake->getHead()->position() == fruit->position()) {
        snake->changeColor(fruit->getColor());
        delete fruit;
        fruit = new Fruit{checkFruit()};
        scene->addItem(fruit);
        scene->addItem(snake->addChunk());
        checkboard[snake->getTail()->position()] = false;

        if (snake->getLength() == 40*30)
            winGame();

        if (snake->getLength() % 5 == 0 && time>=5) {
            time -= time/10;
            timer->start(time);

            emit speedChanged(QString::number(1000/time));
        }
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

void MainWindow::start()
{
    stackedLayout->setCurrentWidget(view);
    timer->start();
}

void MainWindow::endGame()
{
    timer->stop();
    snake->hide();
    fruit->hide();
    auto text = new QGraphicsSimpleTextItem{"HAI PERSO PORCODDIO"};
    text->setPen(QPen{Qt::red});
    text->setPos(view->width() /2 - text->boundingRect().center().x(),
                 view->height()/2 - text->boundingRect().center().y());
    scene->addItem(text);
}

void MainWindow::winGame()
{
    timer->stop();
    auto text = new QGraphicsSimpleTextItem{"HAI VINTO PORCAMADONNA"};
    text->setPen(QPen{Qt::green});
    scene->addItem(text);
}

void MainWindow::showMenu()
{
    timer->stop();
    stackedLayout->setCurrentWidget(menu);
}

void MainWindow::initializeHash()
{
    for (int i = 5; i<width(); i+=10)
        for (int j = 5; j<height(); j+=10)
            checkboard[QPoint{i,j}] = true;

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
