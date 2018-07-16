#include "menu.h"

Menu::Menu(QWidget *parent) : QWidget(parent)
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
            this, &Menu::start);
    connect(saveButton, &QPushButton::clicked,
            this, &Menu::save);
    connect(loadButton, &QPushButton::clicked,
            this, &Menu::load);
    connect(exitButton, &QPushButton::clicked,
            this, &Menu::exit);

}

void Menu::exit()
{
    QApplication::quit();
}
