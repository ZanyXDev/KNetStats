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
    switch(role) {
    case IDRole:
        return false;
    case InterfaceNameRole:
        if (value.canConvert<QString>()) {
            ethDevice.m_interfaceName = value.toString();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case SysDevPathRole:
        if (value.canConvert<QString>()) {
            ethDevice.m_sysDevPath = value.toString();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case CarrierRole:
        if (value.canConvert<bool>()) {
            ethDevice.m_carrier = value.toBool();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case UpdateIntervalRole:
        if (value.canConvert<int>()) {
            ethDevice.m_updateInterval = value.toInt();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case MonitoringRole:
        if (value.canConvert<bool>()) {
            ethDevice.m_monitoring = value.toBool();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case NotificationsRole:
        if (value.canConvert<bool>()) {
            ethDevice.m_notifications = value.toBool();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case ThemeRole:
        if (value.canConvert<int>()) {
            ethDevice.m_theme = value.toInt();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case ChartUplColorRole:
        if (value.canConvert<uint>()) {
            ethDevice.m_chartUplColor = value.toUInt();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case ChartDldColorRole:
        if (value.canConvert<uint>()) {
            ethDevice.m_chartDldColor = value.toUInt();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case ChartBgColorRole:
        if (value.canConvert<uint>()) {
            ethDevice.m_chartBgColor = value.toUInt();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case ChartTransparentBackgroundRole:
        if (value.canConvert<bool>()) {
            ethDevice.m_chartTransparentBackground = value.toBool();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case BRxRole:
        if (value.canConvert<quint64>()) {
            ethDevice.m_bRx = value.toULongLong();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case BTxRole:
        if (value.canConvert<quint64>()) {
            ethDevice.m_bTx = value.toULongLong();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case PRxRole:
        if (value.canConvert<quint64>()) {
            ethDevice.m_pRx = value.toULongLong();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case PTxRole:
        if (value.canConvert<quint64>()) {
            ethDevice.m_pTx = value.toULongLong();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case TotalBytesRxRole:
        if (value.canConvert<quint64>()) {
            ethDevice.m_totalBytesRx = value.toULongLong();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case TotalBytesTxRole:
        if (value.canConvert<quint64>()) {
            ethDevice.m_totalBytesTx = value.toULongLong();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case TotalPktRxRole:
        if (value.canConvert<quint64>()) {
            ethDevice.m_totalPktRx = value.toULongLong();
            emit dataChanged(index, index);
            return true;
        }
        break;
    case TotalPktTxRole:
        if (value.canConvert<quint64>()) {
            ethDevice.m_totalPktTx = value.toULongLong();
            emit dataChanged(index, index);
            return true;
        }
        break;
    default:
        return false;
    }
    return false;
}
