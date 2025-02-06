#include <QtGui/QIcon>
#include <QtGui/QScreen>

#include <QtWidgets/QApplication>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMessageBox>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QTimer>

#include <QtCore/QCoreApplication>
#include <QtCore/QStandardPaths>
#include <QtCore/QTime>
#include <QtCore/QSharedMemory>
#include <QtCore/QLockFile>
#include <QtCore/QTranslator>
#include <QtCore/QScopedPointer>
#include <QtSql/QSqlDatabase>

#ifdef QT_DEBUG
#include <QtCore/QDirIterator>
#include <QtCore/QLoggingCategory>
#endif

#include <singleapplication.h>
#include "messagereciver.h"
#include "databasemanager.h"

int main(int argc, char *argv[]) {

#ifdef QT_DEBUG
    QLocale::setDefault(QLocale::English);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setOrganizationName("io.github.zanyxdev");
    QCoreApplication::setApplicationName("KNetStats");
    QCoreApplication::setApplicationVersion(VERSION_STR);

    // Allocate [MessageReciver] before the engine to ensure that it outlives it !!
    QScopedPointer<MessageReciver>m_msgReciver(new MessageReciver);
    QScopedPointer<DatabaseManager>m_dbManager(new DatabaseManager);

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false); // prevent app from closing, when closing dialog message
    // Separate single instance object (that allows secondary instances)
    SingleApplication single_instance_guard( argc, argv, true );

    // If this is a secondary instance
    if( single_instance_guard.isSecondary() ) {
        QString msg = QObject::tr("%1 already running. Primary instance PID: %2. Primary instance user: %3")
        .arg(QCoreApplication::applicationName())
            .arg(single_instance_guard.primaryPid())
            .arg(single_instance_guard.primaryUser());
        single_instance_guard.sendMessage( msg.toUtf8() );
        return 0;
    } else {
        QString recive_message;
        QObject::connect(&single_instance_guard, &SingleApplication::receivedMessage,
                         m_msgReciver.get(),&MessageReciver::receivedMessage);
    }

    QDir dirAppConfig( QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) );
    if (dirAppConfig.exists() == false)
        dirAppConfig.mkpath(dirAppConfig.path());

    QDir dirAppData( QStandardPaths::writableLocation(QStandardPaths::AppDataLocation ) );
    if (dirAppData.exists() == false)
        dirAppData.mkpath(dirAppData.path());

    QTranslator myappTranslator;
    if (  myappTranslator.load(QLocale(), QLatin1String("knetstats"), QLatin1String("_"), QLatin1String(":/res/i18n")) ){
        app.installTranslator(&myappTranslator);
    }

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/res/qml");
    QQmlContext *context = engine.rootContext();  
    context->setContextProperty("AppVersion",VERSION_STR);
    context->setContextProperty("dirAppConfig",dirAppConfig.path());
    context->setContextProperty("dirAppData",dirAppData.path());

#ifdef QT_DEBUG
    context->setContextProperty("isDebugMode",true);
#else
    context->setContextProperty("isDebugMode",false);
#endif

    const QUrl url(QStringLiteral("qrc:/res/qml/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](const QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    // Register the singleton type provider with QML by calling this
    // function in an initialization function.
    qmlRegisterSingletonInstance("io.github.zanyxdev.knetstats.MessageReciver", 1, 0,"MessageReciver", m_msgReciver.get());
    qmlRegisterSingletonInstance("io.github.zanyxdev.knetstats.DBManager", 1, 0,"DBManager", m_dbManager.get());
    engine.load(url);
    return app.exec();
}
