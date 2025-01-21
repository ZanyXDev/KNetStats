#include "devicestatistic.h"

DeviceStatistic::DeviceStatistic(QObject *parent)
    : QObject{parent}
    , m_device("")
    , m_carrier(false)
    , m_rxBytes(0)
    , m_txBytes(0)
    , m_rxPackets(0)
    , m_txPackets(0)
{}

QString DeviceStatistic::device() const
{
    return m_device;
}

void DeviceStatistic::setDevice(const QString &newDevice)
{
    if (m_device == newDevice)
        return;
    m_device = newDevice;
    emit deviceChanged();
}

bool DeviceStatistic::carrier() const
{
    return m_carrier;
}

void DeviceStatistic::setCarrier(bool newCarrier)
{
    if (m_carrier == newCarrier)
        return;
    m_carrier = newCarrier;
    emit carrierChanged();
}

unsigned long long DeviceStatistic::rxBytes() const
{
    return m_rxBytes;
}

void DeviceStatistic::setRxBytes(unsigned long long newRxBytes)
{
    m_rxBytes = newRxBytes;
}

unsigned long long DeviceStatistic::txBytes() const
{
    return m_txBytes;
}

void DeviceStatistic::setTxBytes(unsigned long long newTxBytes)
{
    m_txBytes = newTxBytes;
}

unsigned long long DeviceStatistic::rxPackets() const
{
    return m_rxPackets;
}

void DeviceStatistic::setRxPackets(unsigned long long newRxPackets)
{
    m_rxPackets = newRxPackets;
}

unsigned long long DeviceStatistic::txPackets() const
{
    return m_txPackets;
}

void DeviceStatistic::setTxPackets(unsigned long long newTxPackets)
{
    m_txPackets = newTxPackets;
}
