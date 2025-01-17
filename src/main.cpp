#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QtCore/QCoreApplication>
#include <QtCore/QTranslator>
#ifdef QT_DEBUG
#include <QtCore/QDirIterator>
#include <QtCore/QLoggingCategory>
#endif

#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtGui/QScreen>



// Declare a user-defined data type to work with an icon in QML
//Q_DECLARE_METATYPE(QSystemTrayIcon::ActivationReason)

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

#ifdef QT_DEBUG
    QLocale::setDefault(QLocale::English);
    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));
#endif

    QCoreApplication::setOrganizationName(PACKAGE_NAME_STR);
    QCoreApplication::setApplicationName(APP_NAME_STR);
    QCoreApplication::setApplicationVersion(VERSION_STR);
    QApplication app(argc, argv);

#ifndef QT_DEBUG
    app.setQuitOnLastWindowClosed(false); // prevent app from closing, when closing dialog message
#endif
    QTranslator myappTranslator;
    if (  myappTranslator.load(QLocale(), QLatin1String("knetstats"), QLatin1String("_"), QLatin1String(":/res/i18n")) ){
        app.installTranslator(&myappTranslator);
    }

    QScreen *screen = qApp->primaryScreen();
#ifdef QT_DEBUG
    qDebug() << "screen->devicePixelRatio():" << screen->devicePixelRatio()
             << "\nscreen->physicalSize():" <<screen->physicalSize()
             << "\nscreen->logicalDotsPerInch():" << screen->logicalDotsPerInch();
#endif

    QQmlApplicationEngine engine;
    engine.addImportPath("qrc:/res/qml");
    QQmlContext *context = engine.rootContext();  
    context->setContextProperty("AppVersion",VERSION_STR);
    bool workMode;
#ifdef QT_DEBUG
    workMode = false;
#else
    workMode = true;
#endif
               context->setContextProperty("isDebugMode",!workMode);
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
