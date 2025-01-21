#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QtQml/qqml.h>


class DeviceStatistic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(bool carrier READ carrier WRITE setCarrier NOTIFY carrierChanged)
    Q_PROPERTY(unsigned long long rxBytes READ rxBytes WRITE setRxBytes NOTIFY rxBytesChanged)
    Q_PROPERTY(unsigned long long txBytes READ txBytes WRITE setTxBytes NOTIFY txBytesChanged)
    Q_PROPERTY(unsigned long long rxPackets READ rxPackets WRITE setRxPackets NOTIFY rxPacketsChanged)
    Q_PROPERTY(unsigned long long txPackets READ txPackets WRITE setTxPackets NOTIFY txPacketsChanged)
    QML_ELEMENT
public:
    explicit DeviceStatistic(QObject *parent = nullptr);

    QString device() const;
    void setDevice(const QString &newDevice);

    bool carrier() const;
    void setCarrier(bool newCarrier);

    unsigned long long rxBytes() const;
    void setRxBytes(unsigned long long newRxBytes);

    unsigned long long txBytes() const;
    void setTxBytes(unsigned long long newTxBytes);

    unsigned long long rxPackets() const;
    void setRxPackets(unsigned long long newRxPackets);

    unsigned long long txPackets() const;
    void setTxPackets(unsigned long long newTxPackets);

signals:
    void deviceChanged();
    void carrierChanged();
    void rxBytesChanged();
    void txBytesChanged();
    void rxPacketsChanged();
    void txPacketsChanged();

private:

    QString m_device;
    bool m_carrier;
    unsigned long long m_rxBytes;
    unsigned long long m_txBytes;
    unsigned long long m_rxPackets;
    unsigned long long m_txPackets;
};

