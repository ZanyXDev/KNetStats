#include "devicemodel.h"

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractItemModel{parent}
{}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IDRole]="id";
    roles[InterfaceNameRole]="interfacename";
    roles[SysDevPathRole]="sysdevpath";
    roles[CarrierRole]="carrier";
    roles[UpdateIntervalRole]="updateinterval";
    roles[MonitoringRole]="monitoring";
    roles[NotificationsRole]="notification";
    roles[ThemeRole]="theme";
    roles[ChartUplColorRole]="chartruplcolor";
    roles[ChartDldColorRole]="chartrdldcolor";
    roles[ChartBgColorRole]="chartrbgcolor";
    roles[ChartTransparentBackgroundRole]="charttransparentbackground";
    roles[BRxRole]="brx";
    roles[BTxRole]="btx";
    roles[PRxRole]="prx";
    roles[PTxRole]="ptx";
    roles[TotalBytesRxRole]="totalbytesrx";
    roles[TotalBytesTxRole]="totalbytestx";
    roles[TotalPktRxRole]="totalpktrx";
    roles[TotalPktTxRole]="totalpkttx";
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
    case IDRole:
        return ethDevice.id;
    case InterfaceNameRole:
        return ethDevice.m_interfaceName;
    case SysDevPathRole:
        return ethDevice.m_sysDevPath;
    case CarrierRole:
        return ethDevice.m_carrier;
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
    case BRxRole:
        return ethDevice.m_bRx;
    case BTxRole:
        return ethDevice.m_bTx;
    case PRxRole:
        return ethDevice.m_pRx;
    case PTxRole:
        return ethDevice.m_pTx;
    case TotalBytesRxRole:
        return ethDevice.m_totalBytesRx;
    case TotalBytesTxRole:
        return ethDevice.m_totalBytesTx;
    case TotalPktRxRole:
        return ethDevice.m_totalPktRx;
    case TotalPktTxRole:
        return ethDevice.m_totalPktTx;
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
    case IDRole:
        break;
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
    case BRxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_bRx = value.toULongLong();
        break;
    case BTxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_bTx = value.toULongLong();
        break;
    case PRxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_pRx = value.toULongLong();
        break;
    case PTxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_pTx = value.toULongLong();
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

