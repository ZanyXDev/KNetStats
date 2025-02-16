#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <QColor>
#include "ethdevice.h"

class DeviceModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DeviceModel(QObject *parent = nullptr);
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
        PacketSpeedTxRole,
        TotalBytesRxRole,
        TotalBytesTxRole,
        TotalPktRxRole,
        TotalPktTxRole,
        BusyStateRole
    };
  // QAbstractItemModel interface
    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:

    QVector<EthDevice> m_data;
};

