#include "runguard.h"

RunGuard::RunGuard( QObject *parent)
    : QObject{parent}
    , m_appKey("")
    , m_appRunTime("")
    , m_message("")
    , m_appRunning(false)
    , m_localServer (new QLocalServer(this))

{    
    // Получаем текущую дату и время в локальном часовом поясе
    QDateTime currentDateTime = QDateTime::currentDateTime();
    // Получаем текущую локаль
    QLocale locale = QLocale::system();
    // Форматируем дату и время для отображения с учетом локали
    m_appRunTime = locale.toString(currentDateTime, QLocale::ShortFormat);
}

RunGuard::~RunGuard()
{
    m_localServer->deleteLater();
}


void RunGuard::handleNewConnection()
{
    QLocalSocket *clientConnection = m_localServer->nextPendingConnection();
    connect(clientConnection, &QLocalSocket::readyRead, this, &RunGuard::readFromSocket);
}

void RunGuard::sendMessage(const QString &appKey,const QString &message)
{
    // Попробуем подключиться к существующему экземпляру
    QLocalSocket socket;
    socket.connectToServer(appKey);
    if (socket.waitForConnected(1000)) { // ожидание подключения (1 секунда)
        socket.write(message.toUtf8());
        socket.flush();
        socket.disconnectFromServer();
        m_appRunning = true;
        emit appRunningChanged();
    }
}

void RunGuard::readFromSocket()
{
    QLocalSocket *socket = qobject_cast<QLocalSocket*>(sender());
    if (socket) {
        QByteArray message = socket->readAll();
        m_message = QString("%1 at %2").arg(QString::fromUtf8(message)).arg(m_appRunTime);
        emit messageChanged();
        socket->deleteLater();
    }
}


void RunGuard::setAppKey(const QString &newAppKey)
{
    qDebug() << Q_FUNC_INFO << m_localServer;
    m_appKey = newAppKey;

    // Попробуем создать локальный сервер
    connect(m_localServer, &QLocalServer::newConnection, this, &RunGuard::handleNewConnection);

    if (!m_localServer->listen( m_appKey )){
        qDebug() <<m_localServer->errorString();
        sendMessage(m_appKey,tr("Another instance will running at %1").arg(m_appRunTime));
    }
}

QString RunGuard::message() const
{
    return m_message;
}


bool RunGuard::appRunning() const
{
    return m_appRunning;
}
