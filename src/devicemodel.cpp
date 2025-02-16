#include "devicemodel.h"

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractItemModel{parent}
{}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[InterfaceNameRole]="interfacename";
    roles[SysDevPathRole]="sysdevpath";
    roles[CarrierRole]="carrier";
    roles[MTURole]="mtu";
    roles[MACRole]="mac";
    roles[IPRole]="ip";
    roles[NetMaskRole]="netmask";
    roles[UpdateIntervalRole]="updateinterval";
    roles[MonitoringRole]="monitoring";
    roles[NotificationsRole]="notification";
    roles[ThemeRole]="theme";
    roles[ChartUplColorRole]="chartruplcolor";
    roles[ChartDldColorRole]="chartrdldcolor";
    roles[ChartBgColorRole]="chartrbgcolor";
    roles[ChartTransparentBackgroundRole]="charttransparentbackground";
    roles[MaxSpeedRole]="maxspeed";
    roles[ByteSpeedRxRole]="bytespeedrx";
    roles[ByteSpeedTxRole]="bytespeetx";
    roles[PacketSpeedRxRole]="packetspeedrx";
    roles[PacketSpeedTxRole]="packetspeedtx";
    roles[TotalBytesRxRole]="totlabytesrx";
    roles[TotalBytesTxRole]="toltalbytestx";
    roles[TotalPktRxRole]="totalpacketsrx";
    roles[TotalPktTxRole]="totalpacketstx";
    roles[BusyStateRole]="busystate";
    return roles;
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_data.size();
}

int DeviceModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 20; // ID, ... TotalPktTxRole
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    const EthDevice& ethDevice = m_data[index.row()];
    switch(role) {   
    case InterfaceNameRole:
        return ethDevice.m_interfaceName;
    case SysDevPathRole:
        return ethDevice.m_sysDevPath;
    case CarrierRole:
        return ethDevice.m_carrier;
    case MTURole:
        return ethDevice.m_MTU;
    case MACRole:
        return ethDevice.m_MAC;
    case IPRole:
        return ethDevice.m_IP;
    case NetMaskRole:
        return ethDevice.m_netmask;
    case UpdateIntervalRole:
        return ethDevice.m_updateInterval;
    case MonitoringRole:
        return ethDevice.m_monitoring;
    case NotificationsRole:
        return ethDevice.m_notifications;
    case ThemeRole:
        return ethDevice.m_theme;
    case ChartUplColorRole:
        return ethDevice.m_chartUplColor;
    case ChartDldColorRole:
        return ethDevice.m_chartDldColor;
    case ChartBgColorRole:
        return ethDevice.m_chartBgColor;
    case ChartTransparentBackgroundRole:
        return ethDevice.m_chartTransparentBackground;        
    case MaxSpeedRole:
        return ethDevice.m_maxSpeed;
    case ByteSpeedRxRole:
        return ethDevice.m_byteSpeedRx;
    case ByteSpeedTxRole:
        return ethDevice.m_byteSpeedTx;
    case PacketSpeedRxRole:
        return ethDevice.m_pktSpeedRx;
    case PacketSpeedTxRole:
        return ethDevice.m_pktSpeedTx;
    case TotalBytesRxRole:
        return ethDevice.m_totalBytesRx;
    case TotalBytesTxRole:
        return ethDevice.m_totalBytesTx;
    case TotalPktRxRole:
        return ethDevice.m_totalPktRx;
    case TotalPktTxRole:
        return ethDevice.m_totalPktTx;
    case BusyStateRole:
        return ethDevice.m_busystate;
    default:
        return QVariant();
    }
}

bool DeviceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= m_data.size())
        return false;
    EthDevice& ethDevice = m_data[index.row()];
    bool flag{false};
    switch(role) {    
    case InterfaceNameRole:
        flag = value.canConvert<QString>();
        if (flag)
            ethDevice.m_interfaceName = value.toString();
        break;
    case SysDevPathRole:
        flag = value.canConvert<QString>();
        if (flag)
            ethDevice.m_sysDevPath = value.toString();
        break;
    case CarrierRole:
        flag = value.canConvert<bool>();
        if (flag)
            ethDevice.m_carrier = value.toBool();
        break;        
    case MTURole:
        flag = value.canConvert<int>();
        if (flag)
            ethDevice.m_MTU = value.toInt();
        break;
    case MACRole:
        flag = value.canConvert<QString>();
        if (flag)
            ethDevice.m_MAC = value.toString();
        break;
    case IPRole:
        flag = value.canConvert<QString>();
        if (flag)
            ethDevice.m_IP = value.toString();
        break;
    case NetMaskRole:
        flag = value.canConvert<QString>();
        if (flag)
            ethDevice.m_netmask = value.toString();
        break;
    case UpdateIntervalRole:
        flag = value.canConvert<int>();
        if (flag)
            ethDevice.m_updateInterval = value.toInt();
        break;
    case MonitoringRole:
        flag = value.canConvert<bool>();
        if (flag)
            ethDevice.m_monitoring = value.toBool();
        break;
    case NotificationsRole:
        flag = value.canConvert<bool>();
        if (flag)
            ethDevice.m_notifications = value.toBool();
        break;
    case ThemeRole:
        flag = value.canConvert<int>();
        if (flag)
            ethDevice.m_theme = value.toInt();
        break;
    case ChartUplColorRole:
        flag = value.canConvert<uint>();
        if (flag)
            ethDevice.m_chartUplColor = value.toUInt();
        break;
    case ChartDldColorRole:
        flag = value.canConvert<uint>();
        if (flag)
            ethDevice.m_chartDldColor = value.toUInt();
        break;
    case ChartBgColorRole:
        flag = value.canConvert<uint>();
        if (flag)
            ethDevice.m_chartBgColor = value.toUInt();
        break;
    case ChartTransparentBackgroundRole:
        flag = value.canConvert<bool>();
        if (flag)
            ethDevice.m_chartTransparentBackground = value.toBool();
        break;
    case MaxSpeedRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_maxSpeed = value.toULongLong();
        break;
    case ByteSpeedRxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_byteSpeedRx = value.toULongLong();
        break;
    case ByteSpeedTxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_byteSpeedTx = value.toULongLong();
        break;
    case PacketSpeedRxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_pktSpeedRx = value.toULongLong();
        break;
    case PacketSpeedTxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_pktSpeedTx = value.toULongLong();
        break;
    case TotalBytesRxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_totalBytesRx = value.toULongLong();
        break;
    case TotalBytesTxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_totalBytesTx = value.toULongLong();
        break;
    case TotalPktRxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_totalPktRx = value.toULongLong();
        break;
    case TotalPktTxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_totalPktTx = value.toULongLong();
        break;
    case BusyStateRole:
        flag = value.canConvert<int>();
        if (flag)
            ethDevice.m_busystate = value.toInt();
        break;
    default:
        flag = false;
    }

    if (flag)
        emit dataChanged(index, index);

    return flag;
}

Qt::ItemFlags DeviceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags; //Qt::ItemIsEnabled;

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    // Добавляем флаги редактирования
    flags |= Qt::ItemIsEditable;

    return flags;
}

