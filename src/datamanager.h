#pragma once

#include <QObject>
#include <QDebug>
#include <QNetworkInterface>
#include <QtQml/qqml.h>
#include <QVariantMap>
#include <QVariant>

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

    Q_INVOKABLE bool setMonitoring(int index, const QVariant &value);
    Q_INVOKABLE bool setNotifications(int index, const QVariant &value);
    Q_INVOKABLE bool setTheme(int index, const QVariant &value);
    Q_INVOKABLE bool setUpdateInterval(int index, const QVariant &value);
    Q_INVOKABLE QVariantMap get(int index) const;

signals:
    void showMessageInSysTray(const QString &message);
    void dataChanged();
private:
    DeviceModel* m_deviceModel;

    bool fillDevice(const QString &interfaceName, EthDevice &m_device);
};

