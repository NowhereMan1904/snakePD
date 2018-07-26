#include "sessionmanager.h"

#include <QFile>
#include <QJsonDocument>

void SessionManager::loadFromJSON(QJsonObject& object)
{
    QFile loadFile("save.Json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    object = loadDoc.object();
}

void SessionManager::saveToJSON(QJsonObject& json)
{
    QFile saveFile("save.Json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument saveDoc(json);
    saveFile.write(saveDoc.toJson());
}

