#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QObject>
#include <QVector>
#include "ethdevice.h"

class EthernetDeviceModel: public QAbstractItemModel
{
       Q_OBJECT
        enum { ValueRole = Qt::DisplayRole };
public:
    explicit EthernetDeviceModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<EthDevice> m_data;
};

