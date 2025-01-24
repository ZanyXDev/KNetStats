#include "ethdevice.h"

EthDevice::EthDevice(QObject *parent)
    : QObject{parent}
 {

 }

 QString EthDevice::deviceName() const
 {
     return m_deviceName;
 }

 void EthDevice::setDeviceName(const QString &newDeviceName)
 {
     if (m_deviceName == newDeviceName)
         return;
     m_deviceName = newDeviceName;
     emit deviceNameChanged();
 }

 QString EthDevice::mtu() const
 {
     return m_mtu;
 }

 void EthDevice::setMtu(const QString &newMtu)
 {
     if (m_mtu == newMtu)
         return;
     m_mtu = newMtu;
     emit mtuChanged();
 }

 QString EthDevice::ip() const
 {
     return m_ip;
 }

 void EthDevice::setIp(const QString &newIp)
 {
     if (m_ip == newIp)
         return;
     m_ip = newIp;
     emit ipChanged();
 }

 QString EthDevice::netmask() const
 {
     return m_netmask;
 }

 void EthDevice::setNetmask(const QString &newNetmask)
 {
     if (m_netmask == newNetmask)
         return;
     m_netmask = newNetmask;
     emit netmaskChanged();
 }

 QString EthDevice::mac() const
 {
     return m_mac;
 }

 void EthDevice::setMac(const QString &newMac)
 {
     if (m_mac == newMac)
         return;
     m_mac = newMac;
     emit macChanged();
 }

 bool EthDevice::carrier() const
 {
     return m_carrier;
 }

 void EthDevice::setCarrier(bool newCarrier)
 {
     if (m_carrier == newCarrier)
         return;
     m_carrier = newCarrier;
     emit carrierChanged();
 }

 bool EthDevice::notification() const
 {
     return m_notification;
 }

 void EthDevice::setNotification(bool newNotification)
 {
     if (m_notification == newNotification)
         return;
     m_notification = newNotification;
     emit notificationChanged();
 }

 bool EthDevice::monitoring() const
 {
     return m_monitoring;
 }

 void EthDevice::setMonitoring(bool newMonitoring)
 {
     if (m_monitoring == newMonitoring)
         return;
     m_monitoring = newMonitoring;
     emit monitoringChanged();
 }

 bool EthDevice::chartTransparentBackground() const
 {
     return m_chartTransparentBackground;
 }

 void EthDevice::setChartTransparentBackground(bool newChartTransparentBackground)
 {
     if (m_chartTransparentBackground == newChartTransparentBackground)
         return;
     m_chartTransparentBackground = newChartTransparentBackground;
     emit chartTransparentBackgroundChanged();
 }

 bool EthDevice::missingInterface() const
 {
     return m_missingInterface;
 }

 void EthDevice::setMissingInterface(bool newMissingInterface)
 {
     if (m_missingInterface == newMissingInterface)
         return;
     m_missingInterface = newMissingInterface;
     emit missingInterfaceChanged();
 }

 QColor EthDevice::ChartUplColor() const
 {
     return m_ChartUplColor;
 }

 void EthDevice::setChartUplColor(const QColor &newChartUplColor)
 {
     if (m_ChartUplColor == newChartUplColor)
         return;
     m_ChartUplColor = newChartUplColor;
     emit ChartUplColorChanged();
 }

 QColor EthDevice::chartDldColor() const
 {
     return m_chartDldColor;
 }

 void EthDevice::setChartDldColor(const QColor &newChartDldColor)
 {
     if (m_chartDldColor == newChartDldColor)
         return;
     m_chartDldColor = newChartDldColor;
     emit chartDldColorChanged();
 }

 QColor EthDevice::chartBgColor() const
 {
     return m_chartBgColor;
 }

 void EthDevice::setChartBgColor(const QColor &newChartBgColor)
 {
     if (m_chartBgColor == newChartBgColor)
         return;
     m_chartBgColor = newChartBgColor;
     emit chartBgColorChanged();
 }

 quint64 EthDevice::rxBytes() const
 {
     return m_rxBytes;
 }

 void EthDevice::setRxBytes(quint64 newRxBytes)
 {
     if (m_rxBytes == newRxBytes)
         return;
     m_rxBytes = newRxBytes;
     emit rxBytesChanged();
 }

 quint64 EthDevice::txBytes() const
 {
     return m_txBytes;
 }

 void EthDevice::setTxBytes(quint64 newTxBytes)
 {
     if (m_txBytes == newTxBytes)
         return;
     m_txBytes = newTxBytes;
     emit txBytesChanged();
 }

 quint64 EthDevice::txPackets() const
 {
     return m_txPackets;
 }

 void EthDevice::setTxPackets(quint64 newTxPackets)
 {
     if (m_txPackets == newTxPackets)
         return;
     m_txPackets = newTxPackets;
     emit txPacketsChanged();
 }

