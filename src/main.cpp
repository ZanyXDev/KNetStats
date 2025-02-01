#pragma once

#include <QtGui/QIcon>
#include <QtGui/QScreen>

#include <QtWidgets/QApplication>
#include <QtWidgets/QSystemTrayIcon>
#include <QtWidgets/QMessageBox>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include <QtCore/QCoreApplication>
#include <QtCore/QTranslator>
#include <QtCore/QStandardPaths>
#include <QtCore/QTime>
#include <QtCore/QSharedMemory>
#include <QtCore/QLockFile>

#ifdef HAVE_TRANSLATIONS
#  include <QTranslator>
#endif


#ifdef QT_DEBUG
#include <QtCore/QDirIterator>
#include <QtCore/QLoggingCategory>
#endif


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
    context->setContextProperty("appKey",QCoreApplication::applicationName().toLower()+".sock");

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
