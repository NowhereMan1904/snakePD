#include "menu.h"

#include "gamecontroller.h"

#include <QPushButton>
#include <QVBoxLayout>

Menu::Menu(GameController* gameController)
{
    auto layout = new QVBoxLayout(this);
    auto continueButton = new QPushButton("Continue");
    auto newGameButton = new QPushButton("New Game");
    auto saveButton = new QPushButton("Save");
    auto loadButton = new QPushButton("Load");
    auto exitButton = new QPushButton("Exit");
    auto settingsButton = new QPushButton("Settings");

    layout->addWidget(newGameButton);
    layout->addWidget(continueButton);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);
    layout->addWidget(exitButton);
    layout->addWidget(settingsButton);

    setFocusProxy(newGameButton);

    connect(continueButton, &QPushButton::clicked,
            gameController, &GameController::continueGame);
    connect(newGameButton, &QPushButton::clicked,
            gameController, &GameController::newGame);
    connect(saveButton, &QPushButton::clicked,
            gameController, &GameController::writeJSON);
    connect(loadButton, &QPushButton::clicked,
            gameController, &GameController::readJSON);
    connect(exitButton, &QPushButton::clicked,
            gameController, &GameController::exit);

}
