#include "ethernetdevicemodel.h"


EthernetDeviceModel::EthernetDeviceModel(QObject *parent)
    : QAbstractItemModel{parent}
{

}

int EthernetDeviceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.size();
}

int EthernetDeviceModel::columnCount(const QModelIndex &parent) const
{

}

QVariant EthernetDeviceModel::data(const QModelIndex &index, int role) const
{

}

QVariant EthernetDeviceModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}

QHash<int, QByteArray> EthernetDeviceModel::roleNames() const
{

}
