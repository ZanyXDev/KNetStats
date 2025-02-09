#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <QColor>

class DeviceModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DeviceModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    enum Roles {        
        InterfaceNameRole = Qt::UserRole + 1,
        SysDevPathRole,
        CarrierRole,
        MTURole,
        MACRole,
        IPRole,
        NetMaskRole,
        UpdateIntervalRole,
        MonitoringRole,
        NotificationsRole,
        ThemeRole,
        ChartUplColorRole,
        ChartDldColorRole,
        ChartBgColorRole,
        ChartTransparentBackgroundRole,
        MaxSpeedRole,
        ByteSpeedRxRole,
        ByteSpeedTxRole,
        PacketSpeedRxRole,
        PacketSpeedTxRole
    };

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

public slots:
    void addDevice(const QString &interfaceName,
                   const QString &sysDevPath,
                   bool carrier,
                   int MTU,
                   const QString &mac,
                   const QString &ip,
                   const QString &netmask,
                   int updateInterval,
                   bool monitoring,
                   bool notifications,
                   int theme,
                   uint chartUplColor,
                   uint chartDldColor,
                   uint chartBgColor,
                   bool chartTransparentBackground);

private:
    struct EthDevice {
        QString m_interfaceName{};
        QString m_sysDevPath{};
        bool m_carrier{false};
        //IP
        int m_MTU{};
        QString m_MAC;
        QString m_IP;
        QString m_netmask;
        // general
        int m_updateInterval{};
        bool m_monitoring{false};
        bool m_notifications{false};
        // icon view
        int m_theme{};
        // chart view
        uint m_chartUplColor{}; // save and restore QColor.rgba() and QColor::fromRgba(value.toUInt());
        uint m_chartDldColor{};
        uint m_chartBgColor{};
        bool m_chartTransparentBackground{false};        
        //	Rx and Tx to bytes and packets
        quint64 m_maxSpeed{};
        quint64 m_byteSpeedRx{};
        quint64 m_byteSpeedTx{};
        quint64 m_pktSpeedRx{};
        quint64 m_pktSpeedTx{};
    };

    QVector<EthDevice> m_data;

};

/**
 *         TotalBytesRxRole,
        TotalBytesTxRole,
        TotalPktRxRole,
        TotalPktTxRole

 *         // Statistics
        quint64 m_totalBytesRx{};
        quint64 m_totalBytesTx{};
        quint64 m_totalPktRx{};
        quint64 m_totalPktTx{};
*/
