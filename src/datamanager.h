#pragma once

#include <QObject>
#include <QDebug>
#include <QNetworkInterface>

#include "devicemodel.h"

class DataManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList interfaceNameModel MEMBER m_interfaceNameModel NOTIFY interfaceNameModelChanged)
public:
    explicit DataManager(QObject *parent = nullptr);
    Q_INVOKABLE void refreshInterfaces();
signals:  
    void interfaceNameModelChanged();

private:
    DeviceModel m_deviceModel;

    QStringList m_interfaceNameModel;
};

