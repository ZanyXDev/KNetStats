#pragma once
#include <QObject>
#include <QMetaType>
#include <QColor>

class EthDevice: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceName
                   READ deviceName WRITE setDeviceName NOTIFY deviceNameChanged FINAL)
    Q_PROPERTY(QString mtu READ mtu WRITE setMtu NOTIFY mtuChanged FINAL)
    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged FINAL)
    Q_PROPERTY(QString netmask READ netmask WRITE setNetmask NOTIFY netmaskChanged FINAL)
    Q_PROPERTY(QString mac READ mac WRITE setMac NOTIFY macChanged FINAL)
    Q_PROPERTY(bool carrier READ carrier WRITE setCarrier NOTIFY carrierChanged FINAL)
    Q_PROPERTY(bool notification READ notification WRITE setNotification NOTIFY notificationChanged FINAL)
    Q_PROPERTY(bool monitoring READ monitoring WRITE setMonitoring NOTIFY monitoringChanged FINAL)
    Q_PROPERTY(bool chartTransparentBackground READ chartTransparentBackground WRITE setChartTransparentBackground NOTIFY chartTransparentBackgroundChanged FINAL)
    Q_PROPERTY(bool missingInterface READ missingInterface WRITE setMissingInterface NOTIFY missingInterfaceChanged FINAL)
    Q_PROPERTY(QColor ChartUplColor READ ChartUplColor WRITE setChartUplColor NOTIFY ChartUplColorChanged FINAL)
    Q_PROPERTY(QColor chartDldColor READ chartDldColor WRITE setChartDldColor NOTIFY chartDldColorChanged FINAL)
    Q_PROPERTY(QColor chartBgColor READ chartBgColor WRITE setChartBgColor NOTIFY chartBgColorChanged FINAL)
    Q_PROPERTY(quint64 rxBytes READ rxBytes WRITE setRxBytes NOTIFY rxBytesChanged FINAL)
    Q_PROPERTY(quint64 txBytes READ txBytes WRITE setTxBytes NOTIFY txBytesChanged FINAL)
    Q_PROPERTY(quint64 txPackets READ txPackets WRITE setTxPackets NOTIFY txPacketsChanged FINAL)

public:
    explicit EthDevice(QObject *parent = nullptr);

    QString deviceName() const;
    QString mtu() const;
    QString ip() const;
    QString netmask() const;
    QString mac() const;
    bool carrier() const;
    bool notification() const;
    bool monitoring() const;
    bool chartTransparentBackground() const;
    bool missingInterface() const;
    QColor ChartUplColor() const;
    QColor chartDldColor() const;
    QColor chartBgColor() const;
    quint64 rxBytes() const;
    quint64 txBytes() const;
    quint64 txPackets() const;

    void setDeviceName(const QString &newDeviceName);
    void setMtu(const QString &newMtu);
    void setIp(const QString &newIp);
    void setNetmask(const QString &newNetmask);
    void setMac(const QString &newMac);
    void setCarrier(bool newCarrier);
    void setNotification(bool newNotification);
    void setMonitoring(bool newMonitoring);
    void setChartTransparentBackground(bool newChartTransparentBackground);
    void setMissingInterface(bool newMissingInterface);
    void setChartUplColor(const QColor &newChartUplColor);
    void setChartDldColor(const QColor &newChartDldColor);
    void setChartBgColor(const QColor &newChartBgColor);
    void setRxBytes(quint64 newRxBytes);
    void setTxBytes(quint64 newTxBytes);
    void setTxPackets(quint64 newTxPackets);

signals:
    void deviceNameChanged();
    void mtuChanged();
    void ipChanged();
    void netmaskChanged();
    void macChanged();
    void carrierChanged();
    void notificationChanged();
    void monitoringChanged();
    void chartTransparentBackgroundChanged();
    void missingInterfaceChanged();
    void ChartUplColorChanged();
    void chartDldColorChanged();
    void chartBgColorChanged();
    void rxBytesChanged();
    void txBytesChanged();
    void txPacketsChanged();

private:
    QString m_deviceName;
    QString m_mtu;
    QString m_ip;
    QString m_netmask;
    QString m_mac;
    bool m_carrier;
    bool m_notification;
    bool m_monitoring;
    bool m_chartTransparentBackground;
    bool m_missingInterface;
    QColor  m_ChartUplColor;
    QColor m_chartDldColor;
    QColor m_chartBgColor;

    quint64 m_rxBytes;
    quint64 m_txBytes;
    quint64 m_rxPackets;
    quint64 m_txPackets;
};

