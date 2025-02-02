#include <QtGui/QIcon>
#include <QtGui/QScreen>

#include <QtWidgets/QApplication>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMessageBox>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <QtCore/QCoreApplication>
#include <QtCore/QStandardPaths>
#include <QtCore/QTime>
#include <QtCore/QSharedMemory>
#include <QtCore/QLockFile>

#include <QTranslator>


#ifdef QT_DEBUG
#include <QtCore/QDirIterator>
#include <QtCore/QLoggingCategory>
#endif

#include <singleapplication.h>

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    bool workMode= true;
#ifdef QT_DEBUG
    QLocale::setDefault(QLocale::English);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));
    workMode = false;
#endif
    QCoreApplication::setOrganizationName("io.github.zanyxdev");
    QCoreApplication::setApplicationName("KNetStats");
    QCoreApplication::setApplicationVersion(VERSION_STR);

    QApplication app(argc, argv);
    // Separate single instance object (that allows secondary instances)
    SingleApplication single_instance_guard( argc, argv, true );
    QString recive_message="123";
    // If this is a secondary instance
    if( single_instance_guard.isSecondary() ) {
        QString msg = QObject::tr("%1 already running. Primary instance PID: %2. Primary instance user: %3")
                          .arg(QCoreApplication::applicationName())
                          .arg(single_instance_guard.primaryPid())
                          .arg(single_instance_guard.primaryUser());
        single_instance_guard.sendMessage( msg.toUtf8() );
        qDebug() << "App already running!";
        qDebug() << "Primary instance PID: " << single_instance_guard.primaryPid();
        qDebug() << "Primary instance user: " << single_instance_guard.primaryUser();
        return 0;
    } else {

        QObject::connect(&single_instance_guard, &SingleApplication::receivedMessage,
                         [=](int instanceId, QByteArray message) {
            /* DO SOMETHING 2*/
            qDebug() << instanceId << message;
            recive_message.fromUtf8(message);
        });


    }

    app.setQuitOnLastWindowClosed(false); // prevent app from closing, when closing dialog message

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
    context->setContextProperty("isDebugMode",!workMode);
    context->setContextProperty("dirAppConfig",dirAppConfig.path());
    context->setContextProperty("dirAppData",dirAppData.path());
    context->setContextProperty("recive_message",recive_message);

    const QUrl url(QStringLiteral("qrc:/res/qml/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](const QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}
