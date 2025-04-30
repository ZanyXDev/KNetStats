#include "datamanager.h"
#include <QDir>
#include <QModelIndex>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

DataManager::DataManager(QObject *parent)
    : QObject{parent}
    , m_deviceModel(new DeviceModel(this))
{
    if (m_deviceModel){
        QObject::connect(m_deviceModel,&DeviceModel::dataChanged,
                         this,&DataManager::dataChanged);
    }
}

DataManager::~DataManager()
{    
    if (m_deviceModel){

        m_deviceModel->deleteLater();
    }
}

void DataManager::refreshInterfaces()
{
    if (!m_deviceModel) return;

    QStringList realInterfaceList;

    auto interfaces = QNetworkInterface::allInterfaces();
    for (auto &it: interfaces) {
        realInterfaceList.append( it.name() );
    }

    QStringList modelInterfaceList = m_deviceModel->getInterfaceList();
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
        m_deviceModel->removeDevice( item );
    }

    for (const QString& item : onlyInReal) {
        EthDevice ethDevice;
        if (fillDevice(item, ethDevice)){
            m_deviceModel->addDevice( ethDevice );
            emit showMessageInSysTray( msg.arg(item).arg(tr("added")));
        }
    }

    for (const QString& item : common) {
        EthDevice ethDevice;
        if (fillDevice(item, ethDevice)){
            m_deviceModel->updateDevice( ethDevice );
            emit showMessageInSysTray( msg.arg(item).arg(tr("updated")));
        }
    }
}

bool DataManager::loadSettings(const QString &appConfigDir)
{
    return false;
}

bool DataManager::setDeviceProperty(int index, const QVariant &value, int role) {
    if (index < 0 || index >= m_deviceModel->rowCount()) return false;
    QModelIndex idx = m_deviceModel->index(index, 0);
    return m_deviceModel->setData(idx, value, role);
}

bool DataManager::saveSettings(const QString &appConfigDir)
{
    qDebug() << "appConfigDir:" << appConfigDir;
    return false;
}

bool DataManager::setMonitoring(int index, const QVariant &value)
{
    return setDeviceProperty(index,value, m_deviceModel->MonitoringRole);
}

bool DataManager::setNotifications(int index, const QVariant &value)
{
    return setDeviceProperty(index,value, m_deviceModel->NotificationsRole);
}

bool DataManager::setTheme(int index, const QVariant &value)
{
    return setDeviceProperty(index,value, m_deviceModel->ThemeRole);
}

bool DataManager::setChartUplColor(int index, const QVariant &value)
{
    return setDeviceProperty(index,value, m_deviceModel->ChartUplColorRole);
}

bool DataManager::setChartDldColor(int index, const QVariant &value)
{
    return setDeviceProperty(index,value, m_deviceModel->ChartDldColorRole);
}

bool DataManager::setChartBgColor(int index, const QVariant &value)
{
    return setDeviceProperty(index,value, m_deviceModel->ChartBgColorRole);
}

bool DataManager::setUpdateInterval(int index, const QVariant &value)
{
    return setDeviceProperty(index,value, m_deviceModel->UpdateIntervalRole);
}

bool DataManager::setTransparentBackground(int index, const QVariant &value)
{
    return setDeviceProperty(index,value, m_deviceModel->ChartTransparentBackgroundRole);
}

QVariantMap DataManager::get(int index) const
{
    QVariantMap m_data;

    if (index < 0 || index >= m_deviceModel->rowCount() )  return m_data;
    const QModelIndex idx = m_deviceModel->index(index,0);

    const  QHash<int, QByteArray> &roles = m_deviceModel->roleNames();
    if (roles.isEmpty() ) return m_data;

    QHashIterator<int, QByteArray> it(roles);
    while (it.hasNext()){
        it.next();
        const QByteArray rolename = it.value();
        m_data[rolename] =m_deviceModel->data(idx,it.key());
    }
    return m_data;
}



//------------------------------ Private --------------------------------------
bool DataManager::fillDevice(const QString &interfaceName, EthDevice &m_device) const
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
    // m_device.m_theme = (interface.type() == QNetworkInterface::Wifi) ? 0 : 1;
    m_device.m_cardType = (interface.type() == QNetworkInterface::Wifi) ? false : true;

    // Обработка IP и маски сети
    if (interface.flags() & QNetworkInterface::IsRunning) {
        QStringList ipAddresses;
        QStringList netmasks;

        for (const QNetworkAddressEntry &addr : interface.addressEntries()) {
            ipAddresses += addr.ip().toString();
            netmasks += addr.netmask().toString();
        }

        m_device.m_IP = ipAddresses.join('\n');
        m_device.m_netmask = netmasks.join('\n');
    } else {
        m_device.m_IP.clear();
        m_device.m_netmask.clear();
    }

    return true;
}
