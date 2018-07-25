#include "menu.h"
#include "sessionmanager.h"

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

    connect(startButton, &QPushButton::clicked,
            gameController, &GameController::start);
    connect(saveButton, &QPushButton::clicked,
            gameController->getSessionManager(), &SessionManager::saveToJSON);
    connect(loadButton, &QPushButton::clicked,
            gameController->getSessionManager(), &SessionManager::loadFromJSON);
    connect(exitButton, &QPushButton::clicked,
            gameController, &GameController::exit);

}
