#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

class DatabaseManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected  NOTIFY connectedChanged FINAL)
    Q_PROPERTY(QString lastError READ lastError  NOTIFY lastErrorChanged FINAL)
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();
    Q_INVOKABLE void testSignal();
//Q_INVOKABLE  QSqlQueryModel* getInterfacesModel();
    //------------ auto getters -----------------------------------------
    bool connectionState() const;
    bool connected() const;
    QString lastError() const;

signals:
    void connectedChanged();
    void lastErrorChanged();

private:
    QSqlDatabase db;
    bool m_connected;
    QString m_lastError;
};

