#-------------------------------------------------
#
# Project created by QtCreator 2018-04-30T22:03:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snakePorcoDio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    snake.cpp \
    fruit.cpp \
    chunksnake.cpp \
    menu.cpp \
    gamecontroller.cpp \
    snakecontroller.cpp \
    sessionmanager.cpp

HEADERS += \
    mainwindow.h \
    snake.h \
    fruit.h \
    chunksnake.h \
    menu.h \
    gamecontroller.h \
    snakecontroller.h \
    sessionmanager.h
