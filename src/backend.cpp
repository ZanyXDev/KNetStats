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

QString BackEnd::currentDevName() const
{
    return m_currentDevName;
}

void BackEnd::setCurrentDevName(const QString &newCurrentDevName)
{
    if (m_currentDevName == newCurrentDevName)
        return;
    m_currentDevName = newCurrentDevName;
    emit currentDevNameChanged();
}
