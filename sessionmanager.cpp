#include "sessionmanager.h"

#include <QFile>
#include <QJsonDocument>

bool SessionManager::loadFromJSON(QJsonObject& object) const
{
    QFile loadFile("save.Json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    object = loadDoc.object();
    return true;
}

void SessionManager::saveToJSON(QJsonObject& json) const
{
    QFile saveFile("save.Json");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument saveDoc(json);
    saveFile.write(saveDoc.toJson());
}

