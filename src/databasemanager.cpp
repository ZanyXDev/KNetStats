#include "databasemanager.h"

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject{parent}
{
    // Создаем подключение к базе данных
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");

    m_connected = db.open();
    (m_connected) ? m_lastError=QObject::tr("Database connected successfully.") :
                    m_lastError=QObject::tr("Could not open database:%1").arg(db.lastError().text());
    emit connectedChanged();
    emit lastErrorChanged();
}

DatabaseManager::~DatabaseManager()
{
    if (db.isOpen()) {
        db.close();
    }
}

void DatabaseManager::testSignal()
{
    emit connectedChanged();
    emit lastErrorChanged();
}


bool DatabaseManager::connected() const
{
    return m_connected;
}

QString DatabaseManager::lastError() const
{
    return m_lastError;
}
