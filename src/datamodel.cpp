#include "datamodel.h"
#include <QSize>

DataModel::DataModel(QObject *parent)
    : QAbstractTableModel{parent}
    , m_data(0)
    , m_xAxis(0,0)
    , m_yAxis(0,0)
    , maxWindowSize(256)
{

}

int DataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.size();
}

int DataModel::columnCount(const QModelIndex &parent) const
{
     Q_UNUSED(parent)
    return 2; // X,Y value
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const QPointF p = m_data[index.row()];

    if (index.column() == 0)
        return p.x();

    return p.y();
}

QVariant DataModel::headerData(int /* section */, Qt::Orientation /* orientation */, int role) const
{
    if (role == Qt::SizeHintRole)
        return QSize(1, 1);
    return QVariant();
}

QHash<int, QByteArray> DataModel::roleNames() const
{
    static QHash<int, QByteArray> roleNames{{ValueRole, "value"}};
    return roleNames;
}


void DataModel::addData(const QPointF &point)
{
    if (m_data.size() == maxWindowSize) {
        beginRemoveRows(QModelIndex(), 0, 0);
        m_data.pop_front();
        endRemoveRows();
        m_xAxis.setX( m_data.isEmpty() ? 0 : m_data.constFirst().x() );
        emit xAxisChanged();
    }

    beginInsertRows(QModelIndex(),  m_data.size(),  m_data.size() );
    m_data.push_back(point);
    endInsertRows();

    m_xAxis.setY(m_data.isEmpty() ? 0 : m_data.constLast().x());
    emit xAxisChanged();

    // check min [QPointF.X] and max values [QPointF.Y]
    if ( point.x() < m_yAxis.x() ){
        m_yAxis.setX( point.x() );
        emit yAxisChanged();
    }
    if ( point.y() > m_yAxis.y() ){
        m_yAxis.setY( point.y() );
        emit yAxisChanged();
    }

}


QPointF DataModel::xAxis() const
{
    return m_xAxis;
}

QPointF DataModel::yAxis() const
{
    return m_yAxis;
}
