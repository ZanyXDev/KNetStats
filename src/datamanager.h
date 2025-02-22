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
    ~DataManager();
    Q_INVOKABLE void refreshInterfaces();
    Q_INVOKABLE bool loadSettings(const  QString &appConfigDir);
signals:
    void interfaceNameModelChanged();
    void showMessageInSysTray(const QString &message);
private:
    DeviceModel m_deviceModel;

    bool fillDevice(const QString &interfaceName, EthDevice &m_device);
};

