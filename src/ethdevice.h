#pragma once
#include  <QString>

struct EthDevice {
    QString m_interfaceName{};
    QString m_sysDevPath{};
    bool m_carrier{false};
    //IP
    int m_MTU{};
    QString m_MAC;
    QString m_IP;
    QString m_netmask;
    // general
    int m_updateInterval{};
    bool m_monitoring{false};
    bool m_notifications{false};
    // icon view
    int m_theme{};
    // chart view
    uint m_chartUplColor{}; // save and restore QColor.rgba() and QColor::fromRgba(value.toUInt());
    uint m_chartDldColor{};
    uint m_chartBgColor{};
    bool m_chartTransparentBackground{false};
    //	Rx and Tx to bytes and packets
    quint64 m_maxSpeed{};
    quint64 m_byteSpeedRx{};
    quint64 m_byteSpeedTx{};
    quint64 m_pktSpeedRx{};
    quint64 m_pktSpeedTx{};
    // Statistics
    quint64 m_totalBytesRx{};
    quint64 m_totalBytesTx{};
    quint64 m_totalPktRx{};
    quint64 m_totalPktTx{};
    int m_busystate{0};
};
