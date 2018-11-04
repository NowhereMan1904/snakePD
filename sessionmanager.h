#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

class QJsonObject;

class SessionManager
{
public:
    explicit SessionManager() = default;

    bool loadFromJSON(QJsonObject&) const;
    void saveToJSON  (QJsonObject&) const;
};

#endif // SESSIONMANAGER_H
