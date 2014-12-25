#include <QSqlDatabase>
#include <QString>

#include "sqlstorage.hpp"

SqlStorage::SqlStorage(QObject *parent) : QObject(parent)
{
    sqldb = new QSqlDatabase();
}

SqlStorage::~SqlStorage()
{

}

void SqlStorage::selectDbType(QString type)
{
    if(type == "postgresql")
        sqldb->addDatabase("QPSQL");
}

void SqlStorage::dbConnect(QString ip, int port, QString username, QString password, QString database)
{
    if(ip.length() == 0)
        return;

    if(port < 1 || port > 65535)
        return;

    if(username.length() == 0)
        return;

    if(password.length() == 0)
        return;

    if(database.length() == 0)
        return;

    sqldb->setHostName(ip);
    sqldb->setPort(port);
    sqldb->setUserName(username);
    sqldb->setPassword(password);
    sqldb->setDatabaseName(database);

    sqldb->open();
}

bool SqlStorage::isConnected()
{
    return sqldb->isOpen();
}
