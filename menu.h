#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>

class GameController;

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(GameController*);
    ~Menu() override = default;

};

#endif // MENU_H
