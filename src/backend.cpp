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
