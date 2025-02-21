#pragma once

#include <QObject>
#include <QDebug>
#include <QNetworkInterface>

#include "devicemodel.h"

class DataManager : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QStringList interfaceNameModel MEMBER m_interfaceNameModel NOTIFY interfaceNameModelChanged)
public:
    explicit DataManager(QObject *parent = nullptr);
    Q_INVOKABLE void refreshInterfaces();
signals:
    void interfaceNameModelChanged();
    void showMessageInSysTray(const QString &message);
private:
    DeviceModel m_deviceModel;

    bool fillDevice(const QString &interfaceName, EthDevice &m_device);
};

