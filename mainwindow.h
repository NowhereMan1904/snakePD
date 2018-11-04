#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class GameController;
class Menu;

class QGraphicsScene;
class QGraphicsView;
class QStackedLayout;
class QLabel;

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
