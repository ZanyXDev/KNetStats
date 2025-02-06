#pragma once

#include <QObject>
#include <QtQml/qqml.h>
#include <QAbstractListModel>

class BackEnd : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit BackEnd(QObject *parent = nullptr);
    // --------------------------------- auto getter --------------------------------------------
    // --------------------------------- auto setter --------------------------------------------
    Q_INVOKABLE void loadFromJson(const QString &jsonFileName);
    Q_INVOKABLE void saveToJson(const QString &jsonFileName);
};
