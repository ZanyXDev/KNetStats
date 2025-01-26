#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QtQml/qqml.h>


class DeviceStatistic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString device READ device WRITE setDevice NOTIFY deviceChanged)
    Q_PROPERTY(bool carrier READ carrier WRITE setCarrier NOTIFY carrierChanged)
    Q_PROPERTY(quint64 rxBytes READ rxBytes WRITE setRxBytes NOTIFY rxBytesChanged)
    Q_PROPERTY(quint64 txBytes READ txBytes WRITE setTxBytes NOTIFY txBytesChanged)
    Q_PROPERTY(quint64 rxPackets READ rxPackets WRITE setRxPackets NOTIFY rxPacketsChanged)
    Q_PROPERTY(quint64 txPackets READ txPackets WRITE setTxPackets NOTIFY txPacketsChanged)
    QML_ELEMENT
public:
    explicit DeviceStatistic(QObject *parent = nullptr);

    QString device() const;
    void setDevice(const QString &newDevice);

    bool carrier() const;
    void setCarrier(bool newCarrier);

    quint64 rxBytes() const;
    void setRxBytes(quint64 newRxBytes);

    quint64 txBytes() const;
    void setTxBytes(quint64 newTxBytes);

    quint64 rxPackets() const;
    void setRxPackets(quint64 newRxPackets);

    quint64 txPackets() const;
    void setTxPackets(quint64 newTxPackets);

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
    quint64 m_rxBytes;
    quint64 m_txBytes;
    quint64 m_rxPackets;
    quint64 m_txPackets;
};

