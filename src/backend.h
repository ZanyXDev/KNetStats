#pragma once

#include <QObject>
#include <QNetworkInterface>
#include <QStringList>

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

signals:

private:
    QStringList *m_interfaceList;
};
