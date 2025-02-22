#include "messagereciver.h"

MessageReciver::MessageReciver(QObject *parent)
    : QObject{parent}
    , m_message("")
{}

MessageReciver::~MessageReciver()
{
  qDebug() << Q_FUNC_INFO;
}

QString MessageReciver::message() const
{
    return m_message;
}

void MessageReciver::setMessage(const QString &newMessage)
{

    if (m_message == newMessage)
        return;
    m_message = newMessage;
    emit messageChanged();
    qDebug() << Q_FUNC_INFO << m_message;
}


void MessageReciver::receivedMessage(quint32 instanceId, QByteArray message)
{
    Q_UNUSED(instanceId)

    m_message = QString::fromUtf8(message);
    emit messageChanged();
      qDebug() << Q_FUNC_INFO << m_message;
}

void MessageReciver::aboutToQuit()
{
    qDebug() << Q_FUNC_INFO << m_message;
}
