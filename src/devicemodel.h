#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <QColor>
#include <QStringList>
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
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;

    QModelIndex findDevice(const QString &interfaceName) const;
    QModelIndex getDevice(int index) const;
    bool removeDevice(const QModelIndex& index);
    bool removeDevice(int row);
    bool removeDevice(const QString &interfaceName);
    bool removeDevices(const QModelIndexList& indexes);
    void clear();

    // QByteArray toByteArray() const;
    // bool fromByteArray(const QByteArray& data);
    const QStringList &getInterfaceList();

public slots:
    void addDevice(const EthDevice &device);
private:        
    QVector<EthDevice> m_data;
    QStringList m_interfaceList;

};

