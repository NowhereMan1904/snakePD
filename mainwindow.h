#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "menu.h"
#include "snake.h"

#include <QWidget>
#include <QGraphicsView>
#include <QStackedLayout>
#include <QJsonObject>

class GameController;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(GameController*, Snake*);
    ~MainWindow() override;

    void keyPressEvent(QKeyEvent *event) override;

    QGraphicsScene* getScene() const;
    void closeMenu() const;
    void showMenu() const;

public slots:

signals:
    void speedChanged(QString);
    void keyPressed(QKeyEvent*);

private:

    QGraphicsView* view;
    QGraphicsScene* scene;

    Menu* menu;

    QStackedLayout* stackedLayout;

};

#endif // MAINWINDOW_H
