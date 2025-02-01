#pragma once

#include <QObject>
#include <QtQml/qqml.h>
#include <QAbstractListModel>


class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ message NOTIFY messageChanged FINAL)
    QML_ELEMENT

public:
    explicit BackEnd(QObject *parent = nullptr);
    // --------------------------------- auto getter --------------------------------------------
    // --------------------------------- auto setter --------------------------------------------
    Q_INVOKABLE void loadFromJson(const QString &jsonFileName);
    Q_INVOKABLE void saveToJson(const QString &jsonFileName);


    QString message() const;

public slots:
    void updateStatistics();
    void reciveMessage(const QString &message);

signals:

    void messageChanged();

private:
    QString m_message;
};
