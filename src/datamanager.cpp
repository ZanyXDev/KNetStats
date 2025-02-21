#include "datamanager.h"

#include <QDir>

DataManager::DataManager(QObject *parent)
    : QObject{parent}
{

}

void DataManager::refreshInterfaces()
{    
    QStringList realInterfaceList;

    auto interfaces = QNetworkInterface::allInterfaces();
    for (auto &it: interfaces) {
        realInterfaceList.append( it.name() );
    }

    QStringList modelInterfaceList = m_deviceModel.getInterfaceList();
    // Преобразуем списки в множества
    QSet<QString> setFromReal(realInterfaceList.begin(),realInterfaceList.end());
    QSet<QString> setFromModel(modelInterfaceList.begin(),modelInterfaceList.end());

    // Находим элементы, которые есть только в setFromReal
    QSet<QString> onlyInReal= setFromReal;
    onlyInReal.subtract(setFromModel);

    // Находим элементы, которые есть только в setFromModel
    QSet<QString> onlyInModel = setFromModel;
    onlyInModel.subtract(setFromReal);

    // Элементы, которые есть в setFromModel и setFromReal
    QSet<QString> common = setFromReal;
    common.intersect(setFromModel);

    QString msg = QObject::tr("%1 device %2.");

    for (const QString& item : onlyInModel) {
        emit showMessageInSysTray( msg.arg(item).arg(tr("removed")));
        m_deviceModel.removeDevice( item );
    }

    for (const QString& item : onlyInReal) {
        EthDevice ethDevice;
        if (fillDevice(item, ethDevice)){
            m_deviceModel.addDevice( ethDevice );
            emit showMessageInSysTray( msg.arg(item).arg(tr("added")));
        }
    }

    for (const QString& item : common) {
        EthDevice ethDevice;
        if (fillDevice(item, ethDevice)){
            m_deviceModel.updateDevice( ethDevice );
            emit showMessageInSysTray( msg.arg(item).arg(tr("updated")));
        }
    }
}

bool DataManager::fillDevice(const QString &interfaceName, EthDevice &m_device)
{
    // Лямбда для проверки существования директории /sys/class/net/interface
    auto interfaceIsValid = [](const QString& sysDevPath) {
        QDir sysDir(sysDevPath);
        return sysDir.exists();
    };

    // Лямбда для проверки статуса Carrier
    auto interfaceIsUp = [](const QString& sysDevPath) {
        /**
         *  /sys/net/<>/carrier can immediately read EOF if the network state is DOWN.
         *  Pin it to 0.
        */
        FILE *fp = fopen((sysDevPath + "carrier").toLatin1(), "r");
        int carrierFlag = 0;
        if (fp) {
            carrierFlag = fgetc(fp);
            carrierFlag = (carrierFlag < 0) ? '0' : carrierFlag;
            fclose(fp);
        }
        return  (carrierFlag == '0') ? false : true;
    };

    // Получаем интерфейс
    auto interface = QNetworkInterface::interfaceFromName(interfaceName);
    if (!interface.isValid()) {
        return false;
    }
    // Заполняем базовую информацию об интерфейсе
    m_device.m_interfaceName = interface.name();
    m_device.m_sysDevPath = "/sys/class/net/" + interface.name() + "/";
    m_device.m_interfaceMissing = interfaceIsValid( m_device.m_sysDevPath );
    m_device.m_carrier = ( m_device.m_interfaceMissing ) ? interfaceIsUp( m_device.m_sysDevPath ): false;
    m_device.m_MTU = interface.maximumTransmissionUnit();
    m_device.m_MAC = interface.hardwareAddress();

    // Определяем тему на основе типа интерфейса
    m_device.m_theme = (interface.type() == QNetworkInterface::Wifi) ? 0 : 1;

    // Обработка IP и маски сети
    if (interface.flags() & QNetworkInterface::IsRunning) {
        QStringList ipAddresses;
        QStringList netmasks;

        for (const QNetworkAddressEntry &addr : interface.addressEntries()) {
            ipAddresses << addr.ip().toString();
            netmasks << addr.netmask().toString();
        }

        m_device.m_IP = ipAddresses.join('\n');
        m_device.m_netmask = netmasks.join('\n');
    } else {
        m_device.m_IP.clear();
        m_device.m_netmask.clear();
    }

    return true;
}


