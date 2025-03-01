#pragma once

#include <QString>
#include <QObject>

struct EthDevice {
    // 27 fields
    QString m_interfaceName{QObject::tr("Unknown")};
    QString m_sysDevPath{QObject::tr("Unknown")};
    bool m_carrier{false};
    bool m_interfaceMissing{false};
    //IP
    int m_MTU{0};
    QString m_MAC{QObject::tr("N/A")};
    QString m_IP{ QObject::tr("Not Connected")};
    QString m_netmask{ QObject::tr("Not Connected") };
    // general
    int m_updateInterval{1000};
    bool m_monitoring{false};
    bool m_notifications{false};
    // icon view
    int m_theme{0};
    bool m_cardType{false};
    // chart view
    uint m_chartUplColor{0}; // save and restore QColor.rgba() and QColor::fromRgba(value.toUInt());
    uint m_chartDldColor{0};
    uint m_chartBgColor{0};
    bool m_chartTransparentBackground{false};
    //	Rx and Tx to bytes and packets
    quint64 m_maxSpeed{0};
    quint64 m_byteSpeedRx{0};
    quint64 m_byteSpeedTx{0};
    quint64 m_pktSpeedRx{0};
    quint64 m_pktSpeedTx{0};

    // Statistics
    quint64 m_totalBytesRx{0};
    quint64 m_totalBytesTx{0};
    quint64 m_totalPktRx{0};
    quint64 m_totalPktTx{0};
    int m_busystate{0};
};
