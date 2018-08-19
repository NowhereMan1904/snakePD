// great rewriting soon :)

#include "gamecontroller.h"

#include <QtQuick/QQuickView>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QQuickView view(QUrl(QStringLiteral("qrc:///mainwindow.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    GameController gameController(view.rootObject());

    return a.exec();
}
