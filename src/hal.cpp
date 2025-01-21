#include "hal.h"

Hal::Hal(QObject *parent)
    : QObject{parent}
    , m_dpr(1)
    , m_physicalDotsPerInch(0)
    , m_devicePixelRatio(0)
    , m_debugMode(false)
    , m_appBuildInfo( QString(tr("This program uses Qt version %1.")).arg(QT_VERSION_STR))
{
#ifdef QT_DEBUG
    m_debugMode = true;
#endif
}


void Hal::updateInfo(){

}

double Hal::getDevicePixelRatio() const{
    int density  = m_physicalDotsPerInch * m_devicePixelRatio;

    return   density >= 480 ? 3 :
               density >= 320 ? 2 :
               density >= 240 ? 1.5 : 1;
}

bool Hal::getDebugMode() const
{
    return m_debugMode;
}


void Hal::setDebugMode(bool newDebugmode){
    if (m_debugMode == newDebugmode){
        return;
    }
    m_debugMode = newDebugmode;
}

void Hal::setDotsPerInch(qreal m_dpi)
{
    if (m_physicalDotsPerInch == m_dpi){
        return;
    }
    m_physicalDotsPerInch = m_dpi;
}

void Hal::setDevicePixelRatio(qreal m_dpr)
{
    if (m_devicePixelRatio == m_dpr){
        return;
    }
    m_devicePixelRatio = m_dpr;
}

/*!
 * \brief Make docs encourage readers to query locale right
 * \sa https://codereview.qt-project.org/c/qt/qtdoc/+/297560
 */
void Hal::createAppFolder(){
    ///TODO check permissions
    QDir dirAppConfig( QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) );
    if (dirAppConfig.exists() == false) {
        dirAppConfig.mkpath(dirAppConfig.path());
    }
    QDir dirAppData( QStandardPaths::writableLocation(QStandardPaths::AppDataLocation ) );
    if (dirAppData.exists() == false) {
        dirAppData.mkpath(dirAppData.path());
    }
#ifdef QT_DEBUG
    qDebug() <<"dirAppConfig.path():" <<dirAppConfig.path();
    qDebug() <<"dirAppData.path():" <<dirAppData.path();
#endif
}

QString Hal::getAppBuildInfo() {
    return m_appBuildInfo;
}
