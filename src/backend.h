#pragma once

#include <QObject>
#include <QtGlobal>
#include <QNetworkInterface>
#include <QStringList>
#include <QFile>
#include <QtQml/qqml.h>

#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

#ifdef QT_DEBUG
#include <QDebug>
#endif
#include <QAbstractTableModel>


class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString currentDevName READ currentDevName WRITE setCurrentDevName NOTIFY currentDevNameChanged)
    QML_ELEMENT

public:
    explicit BackEnd(QObject *parent = nullptr);
    // --------------------------------- auto getter --------------------------------------------
    QString userName() const;
    QString currentDevName() const;
    // --------------------------------- auto setter --------------------------------------------
    void setUserName(const QString &newUserName);
    void setCurrentDevName(const QString &newCurrentDevName);

signals:
    void userNameChanged();

    void deviceNameChanged();

    void currentDevNameChanged();

private:
    QString m_userName;

    QString m_currentDevName;
};
