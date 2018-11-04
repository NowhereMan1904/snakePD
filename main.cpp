#include "gamecontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameController gameController;

    return a.exec();
}
