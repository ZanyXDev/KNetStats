#include "devicemodel.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractListModel{parent}
{}

DeviceModel::~DeviceModel()
{
 qDebug() << Q_FUNC_INFO;
}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[InterfaceNameRole]="interfacename";
    roles[SysDevPathRole]="sysdevpath";
    roles[CarrierRole]="carrier";
    roles[InterfaceMissingRole]="interfacemissing";
    roles[MTURole]="mtu";
    roles[MACRole]="mac";
    roles[IPRole]="ip";
    roles[NetMaskRole]="netmask";
    roles[UpdateIntervalRole]="updateinterval";
    roles[MonitoringRole]="monitoring";
    roles[NotificationsRole]="notification";
    roles[ThemeRole]="theme";
    roles[CardTypeRole]="cardtype";
    roles[ChartUplColorRole]="chartuplcolor";
    roles[ChartDldColorRole]="chartdldcolor";
    roles[ChartBgColorRole]="chartbgcolor";
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
    return parent.isValid() ? 0 : this->roleNames().count();
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
    case InterfaceMissingRole:
        return ethDevice.m_interfaceMissing;
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
    case CardTypeRole:
        return ethDevice.m_cardType;
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
    case InterfaceMissingRole:
        flag = value.canConvert<bool>();
        if (flag)
            ethDevice.m_interfaceMissing = value.toBool();
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
    case CardTypeRole:
        flag = value.canConvert<bool>();
        if (flag)
            ethDevice.m_cardType = value.toBool();
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
    case PacketSpeedTxRole:
        flag = value.canConvert<quint64>();
        if (flag)
            ethDevice.m_pktSpeedTx = value.toULongLong();
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

    if (flag) emit dataChanged(index, index); // Always dataChanged first column in row. is is valid ???

    return flag;
}

Qt::ItemFlags DeviceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QModelIndex DeviceModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) return QModelIndex();
    return createIndex(row, column);
}

QModelIndex DeviceModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex(); // Плоская структура данных
}

QModelIndex DeviceModel::findDevice(const QString &interfaceName) const
{
    /**
     * @brief std::find_if получает начало и конец QVector
     * Лямбда-функция проверяет каждое значение поля m_interfaceName
     * При совпадении возвращается итератор на найденный элемент
     * Важные замечания по использованию кода:
     * Проверяйте результат через m_data.end() перед использованием найденного элемента
     * Если элемент не найден, it будет равен m_data.end()
     * Для получения индекса найденного элемента можно использовать:
     * int index = std::distance(m_data.begin(), it);
     */
    auto it = std::find_if(m_data.begin(), m_data.end(),
                           [&](const EthDevice& device) {
                               return device.m_interfaceName == interfaceName;
                           });
    if (it != m_data.end()) {
        int idx = std::distance(m_data.begin(), it);
        return index(idx, 0);
    }
    return QModelIndex();
}

QModelIndex DeviceModel::getDevice(int index) const
{
    if (index < 0 || index >= m_data.size()) {
        return QModelIndex(); // Возврат недействительного индекса
    }
    return createIndex(index, 0); // Создаём индекс для первой колонки
}

bool DeviceModel::removeDevice(const QModelIndex &index)
{
    if (!index.isValid() || index.row() >= m_data.size()) {
        return false;
    }

    beginRemoveRows(QModelIndex(), index.row(), index.row());
    m_data.removeAt(index.row());
    endRemoveRows();
    return true;
}

bool DeviceModel::removeDevice(int row)
{
    return removeDevice(index(row, 0));
}

bool DeviceModel::removeDevice(const QString &interfaceName)
{
    return removeDevice( findDevice( interfaceName ));
}

bool DeviceModel::removeDevices(const QModelIndexList &indexes)
{
    if (indexes.isEmpty()) {
        return false;
    }

    // Сортируем индексы по убыванию для корректного удаления
    QModelIndexList sortedIndexes = indexes;
    std::sort(sortedIndexes.begin(), sortedIndexes.end(),
              [](const QModelIndex& a, const QModelIndex& b) {
                  return a.row() > b.row();
              });

    bool success = true;
    for (const QModelIndex& index : sortedIndexes) {
        success &= removeDevice(index);
    }
    return success;
}

void DeviceModel::clear()
{
    beginResetModel();
    m_data.clear();
    endResetModel();
}

const QStringList &DeviceModel::getInterfaceList()
{
    m_interfaceList.clear();

    for (const auto& device : m_data) {
        m_interfaceList.append(device.m_interfaceName);
    }

    return m_interfaceList;
}


void DeviceModel::addDevice(const EthDevice &device)
{
    QModelIndex existingIndex = findDevice(device.m_interfaceName);
    if (existingIndex.isValid()) {
        removeDevice(existingIndex);
    }
    updateDevice( device );
}

void DeviceModel::updateDevice(const EthDevice &device)
{
    QModelIndex index = findDevice(device.m_interfaceName);
    if (index.isValid()) {
        setData(index, device.m_carrier, CarrierRole);
        setData(index, device.m_interfaceMissing, InterfaceMissingRole);
        setData(index, device.m_MTU, MTURole);
        setData(index, device.m_MAC, MACRole);
        setData(index, device.m_IP, IPRole);
        setData(index, device.m_netmask, NetMaskRole);
        setData(index, device.m_theme, ThemeRole);
        setData(index, device.m_cardType, CardTypeRole);
    }else{
        beginInsertRows(QModelIndex(), m_data.size(), m_data.size());
        m_data.append(device);
        endInsertRows();
    }
    qDebug() <<Q_FUNC_INFO <<  "m_data.size():"<<m_data.size();
}







