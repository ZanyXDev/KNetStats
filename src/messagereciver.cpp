#include "messagereciver.h"

MessageReciver::MessageReciver(QObject *parent)
    : QObject{parent}
    , m_message("")
{}

QString MessageReciver::message() const
{
    return m_message;
}

void MessageReciver::setMessage(const QString &newMessage)
{

    if (m_message == newMessage) return;
    m_message = newMessage;
    emit messageChanged();
}


void MessageReciver::receivedMessage(quint32 instanceId, QByteArray message)
{
    Q_UNUSED(instanceId)

    m_message = QString::fromUtf8(message);
    emit messageChanged();
}

