#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "menu.h"
#include "gamecontroller.h"
#include "snake.h"

#include <QWidget>
#include <QGraphicsView>
#include <QStackedLayout>
#include <QJsonObject>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(GameController*, Snake*);
    ~MainWindow() override;

    void keyPressEvent(QKeyEvent *event) override;

    QGraphicsScene* getScene() const;
    void closeMenu() const;

public slots:

signals:
    void speedChanged(QString);

private:
    void showMenu();

    QGraphicsView* view;
    QGraphicsScene* scene;

    Menu* menu;

    QStackedLayout* stackedLayout;

};

#endif // MAINWINDOW_H
