#include "backend.h"


BackEnd::BackEnd(QObject *parent)
    : QObject{parent} 
{
    connect(&m_tasks, &PeriodicTask::taskCompleted, this, &BackEnd::reciveStatistic);

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

void BackEnd::updateStatistics()
{
    refreshInterfaces();
    m_tasks.setDeviceList(m_interfaces);
}

void BackEnd::refreshInterfaces()
{
    m_interfaces.clear();

    for (auto &it:  QNetworkInterface::allInterfaces()) {
        m_interfaces.append(it.name());
        //KNetStats::readInterfaceConfig(it.name(), &mConfig[it.name()]);
    }

}

void BackEnd::reciveStatistic(const QString &device, bool carrier, unsigned long long rxBytes, unsigned long long txBytes, unsigned long long rxPackets, unsigned long long txPackets)
{
    qDebug() <<device << carrier << rxBytes << txBytes << rxPackets << txPackets;
}
