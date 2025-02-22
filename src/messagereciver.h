#pragma once

#include <QObject>
#include <QDebug>
class MessageReciver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged FINAL)
public:
    explicit MessageReciver(QObject *parent = nullptr);
    ~MessageReciver();
    QString message() const;
    void setMessage(const QString &newMessage);

public slots:
    void receivedMessage( quint32 instanceId, QByteArray message );
    void aboutToQuit();
signals:
    void messageChanged();
private:
    QString m_message;
};

