#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <QColor>

class DeviceModel : public QAbstractItemModel
{
public:
    explicit DeviceModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    enum Roles {
        IDRole = Qt::UserRole + 1,
        InterfaceNameRole,
        SysDevPathRole,
        CarrierRole,
        UpdateIntervalRole,
        MonitoringRole,
        NotificationsRole,
        ThemeRole,
        ChartUplColorRole,
        ChartDldColorRole,
        ChartBgColorRole,
        ChartTransparentBackgroundRole,
        BRxRole,
        BTxRole,
        PRxRole,
        PTxRole,
        TotalBytesRxRole,
        TotalBytesTxRole,
        TotalPktRxRole,
        TotalPktTxRole
    };

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;


private:
    struct EthDevice {
        int id{};
        QString m_interfaceName{};
        QString m_sysDevPath{};
        bool m_carrier{false};
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
        quint64 m_bRx{};
        quint64 m_bTx{};
        quint64 m_pRx{};
        quint64 m_pTx{};
        // Statistics
        quint64 m_totalBytesRx{};
        quint64 m_totalBytesTx{};
        quint64 m_totalPktRx{};
        quint64 m_totalPktTx{};
    };

    QVector<EthDevice> m_data;

};


