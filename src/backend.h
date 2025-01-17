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
    QML_ELEMENT
public:
    explicit BackEnd(QObject *parent = nullptr);
    QString userName() const;
    void setUserName(const QString &newUserName);
signals:
    void userNameChanged();
private:
    QString m_userName;
};
