#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "menu.h"
#include "snake.h"

#include <QGraphicsView>
#include <QStackedLayout>
#include <QWidget>

class GameController;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(GameController*, Snake*);
    ~MainWindow() override = default;

    void keyPressEvent(QKeyEvent*) override;

    QGraphicsScene* getScene() const;

    void closeMenu();
    void showMenu();

signals:
    void keyPressed(QKeyEvent*);

private:
    QGraphicsView*  view;
    QGraphicsScene* scene;
    Menu*           menu;
    QStackedLayout* stackedLayout;
};

#endif // MAINWINDOW_H
