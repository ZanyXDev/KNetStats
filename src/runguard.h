#pragma once

#include <QObject>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
#include <QtQml/qqml.h>
#include <QtCore/QDateTime>
#include <QtCore/QLocale>

class RunGuard : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString message    READ message NOTIFY messageChanged)
    Q_PROPERTY(bool appRunning READ appRunning  NOTIFY appRunningChanged FINAL)
public:
    explicit RunGuard(QObject *parent = nullptr);
    ~RunGuard();
    Q_INVOKABLE void setAppKey(const QString &newAppKey);
    QString message() const;
    bool appRunning() const;

signals:
    void messageChanged();

    void appRunningChanged();

private slots:
    void handleNewConnection();
    void sendMessage(const QString &appKey,const QString &message);
    void readFromSocket();
private:
    QString m_appKey;    
    QString m_appRunTime;
    QString m_message;
    bool m_appRunning;
    QLocalServer *m_localServer;
};

