#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "menu.h"
#include "snake.h"

#include <QGraphicsView>
#include <QStackedLayout>
#include <QWidget>
#include <QLabel>

class GameController;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(GameController*);
    ~MainWindow() override = default;

    void keyPressEvent(QKeyEvent*) override;

    QGraphicsScene* getScene() const;

    void showView();
    void showMenu();
    void showLoose();

signals:
    void keyPressed(QKeyEvent*);

private:
    QGraphicsView*  view;
    QGraphicsScene* scene;
    Menu*           menu;
    QLabel*        loose;
    QStackedLayout* stackedLayout;
};

#endif // MAINWINDOW_H
