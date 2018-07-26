#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>
#include <QJsonObject>

class SessionManager : public QObject
{
    Q_OBJECT
public:
    explicit SessionManager(QObject *parent = nullptr);

    void loadFromJSON(QJsonObject&);
    void saveToJSON(QJsonObject&);

signals:

public slots:
};

#endif // SESSIONMANAGER_H
