#include "backend.h"


BackEnd::BackEnd(QObject *parent)
    : QObject{parent} 
{

}


QString BackEnd::userName() const
{
    return m_userName;
}

void BackEnd::setUserName(const QString &newUserName)
{
    if (m_userName == newUserName)
        return;
    m_userName = newUserName;
    emit userNameChanged();
}

QString BackEnd::deviceName() const
{
    return m_deviceName;
}

void BackEnd::setDeviceName(const QString &newDeviceName)
{
    if (m_deviceName == newDeviceName)
        return;
    m_deviceName = newDeviceName;
    emit deviceNameChanged();
}
