#pragma once

#include <QObject>
#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QDebug>

class Hal : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double devicePixelRatio
                   READ getDevicePixelRatio
                       NOTIFY devicePixelRatioChanged);
    Q_PROPERTY(QString appBuildInfo READ getAppBuildInfo
                   NOTIFY appBuildInfoChanged);

public:
    explicit Hal(QObject *parent = nullptr);

    bool getDebugMode() const;
    double getDevicePixelRatio() const;
    void setDebugMode(bool newDebugmode);
    void setDotsPerInch(qreal m_dpi);
    void setDevicePixelRatio(qreal m_dpr);
    void createAppFolder();

public slots:
    void updateInfo();
    QString getAppBuildInfo();

signals:
    void devicePixelRatioChanged();
    void appBuildInfoChanged();

private:
    double m_dpr; // DevicePixelRatio
    qreal m_physicalDotsPerInch;
    qreal m_devicePixelRatio;   
    bool m_debugMode;
    QString m_appBuildInfo;
};

