#pragma once
#include <QObject>
#include <QTimer>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QStringList>

#ifdef QT_DEBUG
#include <QDebug>
#endif

struct DeviceStatBackgroundResult {
    QString device;
    bool carrier;
    unsigned long long rxBytes;
    unsigned long long txBytes;
    unsigned long long rxPackets;
    unsigned long long txPackets;
};

class PeriodicTask : public QObject
{
    Q_OBJECT
public:
    explicit PeriodicTask(QObject *parent = nullptr);    
    void start();
    void stop();

signals:
    void taskCompleted(const QString &device,
                       bool carrier,
                       unsigned long long rxBytes,
                       unsigned long long txBytes,
                       unsigned long long rxPackets,
                       unsigned long long txPackets );
public slots:
    void setDeviceList(const QStringList &newDeviceList);

private slots:
    void runTask();
    void performBackgroundWork(const QString& task);

private:
    QTimer m_timer;                 // Таймер для запуска задач
    QFutureWatcher<void> m_futureWatcher; // Наблюдатель для отслеживания результата
    QStringList m_deviceList;
};

