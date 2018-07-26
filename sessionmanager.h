#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QJsonObject>

class SessionManager
{
public:
    explicit SessionManager() = default;

    void loadFromJSON(QJsonObject&);
    void saveToJSON(QJsonObject&);

};

#endif // SESSIONMANAGER_H
