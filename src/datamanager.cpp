#include "datamanager.h"

DataManager::DataManager(QObject *parent)
    : QObject{parent}
{

}

void DataManager::refreshInterfaces()
{
    m_interfaceNameModel.clear();

    auto interfaces = QNetworkInterface::allInterfaces();
    for (auto &it: interfaces) {
        m_interfaceNameModel.append( it.name() );
        qDebug() << it.name();
      //  readInterfaceConfig( it.name() );
        emit interfaceNameModelChanged();
    }

}
