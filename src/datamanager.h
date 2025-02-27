#pragma once

#include <QObject>
#include <QDebug>
#include <QNetworkInterface>
#include <QtQml/qqml.h>

#include "devicemodel.h"

class DataManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(DeviceModel* deviceModel READ deviceModel CONSTANT)
public:
    explicit DataManager(QObject *parent = nullptr);
    ~DataManager();
    Q_INVOKABLE void refreshInterfaces();
    Q_INVOKABLE bool loadSettings(const  QString &appConfigDir);
    DeviceModel* deviceModel() const { return m_deviceModel; }
signals:
    void showMessageInSysTray(const QString &message);

private:
     DeviceModel* m_deviceModel;

    bool fillDevice(const QString &interfaceName, EthDevice &m_device);
};

