# Data structure

## File `configure.h`
```cpp
struct ViewOptions {
    // general
    int mUpdateInterval;
    bool mMonitoring;
    bool mNotifications;
    // icon view
    int mTheme;
    // chart view
    QString mChartUplColor;
    QString mChartDldColor;
    QString mChartBgColor;
    bool mChartTransparentBackground;
};

typedef QMap<QString, ViewOptions> OptionsMap;

class Configure
private:
  OptionsMap mConfig;
  
```

Список всех интерфейсов
`
  auto interfaces = QNetworkInterface::allInterfaces();
  interfaces == QList(QNetworkInterface)
`

## File `knetstatsview.h`
```cpp
class KNetStatsView
public:
enum BUFFER_SIZES {
    HISTORY_SIZE = 50,    // Tamanho do historico.
    SPEED_BUFFER_SIZE = 10    // Tamanho do buffer usado para calcular a velocidade
};

//	Rx e Tx to bytes and packets
unsigned long long mBRx{}, mBTx{}, mPRx{}, mPTx{};
// Statistics
unsigned long long mTotalBytesRx{}, mTotalBytesTx{}, mTotalPktRx{}, mTotalPktTx{};
// Speed buffers
double mSpeedBufferRx[SPEED_BUFFER_SIZE]{}, mSpeedBufferTx[SPEED_BUFFER_SIZE]{};
double mSpeedBufferPRx[SPEED_BUFFER_SIZE]{}, mSpeedBufferPTx[SPEED_BUFFER_SIZE]{};
// pointer to current speed buffer position
int mSpeedBufferPtr{};
int mSpeedHistoryPtr{};

// History buffer TODO: Make it configurable!
double mSpeedHistoryRx[HISTORY_SIZE]{};
double mSpeedHistoryTx[HISTORY_SIZE]{};
double mMaxSpeed{};
int mMaxSpeedAge{};
private:
  QString mSysDevPath;            // Path to the device.
  bool mCarrier;                    // Interface carrier is on?
  bool mFirstUpdate;
  

updateStats(){
unsigned long long brx = readInterfaceNumValue("rx_bytes");
unsigned long long btx = readInterfaceNumValue("tx_bytes");
unsigned long long prx = readInterfaceNumValue("rx_packets");
unsigned long long ptx = readInterfaceNumValue("tx_packets");

}

```

### Decsribe

#Global var
HISTORY_SIZE = 1024 
SPEED_BUFFER_SIZE = 128

```cpp

Model
  RootItem
    |
    |-m_interfaceName,m_sysDevPath,m_carrier,m_updateInterval,m_monitoring,mNotifications,m_theme,
      m_chartUplColor,m_chartDldColor,m_chartBgColor,m_chartTransparentBackground,
      m_totalBytesRx, m_totalBytesTx, m_totalPktRx, m_totalPktTx, m_maxSpeed, m_maxSpeedAge,
      m_speedBufferRx,m_speedBufferTx,m_speedBufferPRx,  m_speedBufferPTx,  m_speedHistoryRx,   m_speedHistoryTx
          |-                 |-                   |-                 |-              |-                 |-





//  Interface
  QString m_interfaceName
  QString m_sysDevPath;            // Path to the device.
  bool m_carrier;                    // Interface carrier is on?
  bool m_firstUpdate; 
  
  int m_updateInterval;
  bool m_monitoring;
  bool mNotifications;
  // icon view
  int mTheme;
  // chart view
  QString mChartUplColor;
  QString mChartDldColor;
  QString mChartBgColor;
  bool mChartTransparentBackground;
```  
