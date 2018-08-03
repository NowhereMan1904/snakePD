#include "menu.h"

#include "gamecontroller.h"

#include <QPushButton>
#include <QVBoxLayout>

Menu::Menu(GameController* gameController)
{
    auto layout = new QVBoxLayout(this);
    auto startButton = new QPushButton("Start");
    auto saveButton = new QPushButton("Save");
    auto loadButton = new QPushButton("Load");
    auto exitButton = new QPushButton("Exit");
    auto settingsButton = new QPushButton("Settings");

    layout->addWidget(startButton);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);
    layout->addWidget(exitButton);
    layout->addWidget(settingsButton);

    setFocusProxy(startButton);

    connect(startButton, &QPushButton::clicked,
            gameController, &GameController::start);
    connect(saveButton, &QPushButton::clicked,
            gameController, &GameController::writeJSON);
    connect(loadButton, &QPushButton::clicked,
            gameController, &GameController::readJSON);
    connect(exitButton, &QPushButton::clicked,
            gameController, &GameController::exit);

}
