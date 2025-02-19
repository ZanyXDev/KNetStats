#include "datamanager.h"

DataManager::DataManager(QObject *parent)
    : QObject{parent}
{

}

/**
     * @brief checking:
     *  1. realInterfaceList ([Interface_Name] absent) and modelInterfaceList ([Interface_Name] exist)
     *     -> delete ([Interface_Name]) from model and emit signal showSysTrayMessage("[Interface_Name] removed")
     *  2. realInterfaceList ([Interface_Name] exist) and modelInterfaceList ([Interface_Name] absent)
     *     -> add (interface) to model and emit signal showSysTrayMessage("[Interface_Name] added")
     *  3. foreach item in the model and check field carrier
     *     -> if Carrier state realInterface  not equ Carrier state in the model
     *          -> set  Carrier state   and emit signal showSysTrayMessage("[Interface_Name] carrier changet to [ Carrier state]")
     */
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

    // Находим элементы, которые есть только в realInterfaceList
    QSet<QString> onlyInReal = setFromReal - setFromModel;
    // Находим элементы, которые есть только в modelInterfaceList
    QSet<QString> onlyInModel = setFromModel - setFromReal;

    // Находим общие элементы
    QSet<QString> common = setFromReal & setFromReal;

    // Выводим результаты
    qDebug() << "Элементы только в первом списке:";
    for (const QString& item : onlyInList1) {
        qDebug() << item;
    }

    qDebug() << "\nЭлементы только во втором списке:";
    for (const QString& item : onlyInList2) {
        qDebug() << item;
    }

    qDebug() << "\nОбщие элементы:";
    for (const QString& item : common) {
        qDebug() << item;
    }
}
