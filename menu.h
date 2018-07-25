#ifndef MENU_H
#define MENU_H

#include "gamecontroller.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QApplication>

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(GameController*);

signals:
    void start();
    void save();
    void load();

public slots:
};

#endif // MENU_H
