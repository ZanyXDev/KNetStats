#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QPointF>
#include <QModelIndex>

class DataModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QPointF xAxis READ xAxis NOTIFY xAxisChanged)
    Q_PROPERTY(QPointF yAxis READ yAxis NOTIFY yAxisChanged)

    enum { ValueRole = Qt::DisplayRole };

public:
    explicit DataModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addData(const QPointF &point);

    QPointF xAxis() const;

    QPointF yAxis() const;

signals:
    void xAxisChanged();
    void yAxisChanged();

private:
    QVector<QPointF> m_data;
    QPointF m_xAxis;
    QPointF m_yAxis;
    int maxWindowSize;
};


