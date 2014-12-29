#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDriver>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QVariant>
#include <QDebug>

#include "sqlstorage.hpp"
#include "config.hpp"

SqlStorage::SqlStorage(QObject *parent) : QObject(parent)
{
    sqldb = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));

    queue = new QQueue<InverterData*>();

    timer = new QTimer();
    timer->setInterval(SMLGR_CONFIG_DEFAULT_SQL_INTERVAL);

    connect(timer, SIGNAL(timeout()), this, SLOT(copyQueueToDatabase()));
}

SqlStorage::~SqlStorage()
{
    timer->stop();
    delete timer;

    delete queue;

    sqldb->close();
    delete sqldb;
}

void SqlStorage::start()
{
    timer->start();
}

void SqlStorage::stop()
{
    timer->stop();
}

void SqlStorage::config(QString ip, int port, QString username, QString password, QString database)
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
}

void SqlStorage::addDataIntoQueue(InverterData data)
{
    InverterData* item = new InverterData(data);

    queue->enqueue(item);

    qDebug() << "DATABASE" << "COUNT" << queue->count();
}

void SqlStorage::copyQueueToDatabase()
{
    if(!sqldb->open()) {
        qDebug() << sqldb->lastError().driverText();
        return;
    }

    while(!queue->isEmpty()) {
        InverterData* elem = queue->head();

        QString sqlstring = "INSERT INTO history (whenquery, UDC, IDC, UL1, IL1, PAC, PRL, TKK, TNF, KDY) VALUES"
                            "( :whenquery , :UDC , :IDC , :UL1 , :IL1 , :PAC , :PRL , :TKK , :TNF , :KDY );";

        QSqlQuery sqlquery(*sqldb);
        sqlquery.prepare(sqlstring);

        sqlquery.bindValue(":whenquery", QVariant(elem->getDatetime()));
        sqlquery.bindValue(":UDC", QVariant((int) (elem->getUdc() * 10)));
        sqlquery.bindValue(":IDC", QVariant((int) (elem->getIdc() * 100)));
        sqlquery.bindValue(":UL1", QVariant((int) (elem->getUl1() * 10)));
        sqlquery.bindValue(":IL1", QVariant((int) (elem->getIl1() * 100)));
        sqlquery.bindValue(":PAC", QVariant((int) (elem->getPac() * 2)));
        sqlquery.bindValue(":PRL", QVariant((int) (elem->getPrl())));
        sqlquery.bindValue(":TKK", QVariant((int) (elem->getTkk())));
        sqlquery.bindValue(":TNF", QVariant((int) (elem->getTnf() * 100)));
        sqlquery.bindValue(":KDY", QVariant((int) (elem->getKdy() * 10)));

        if(!sqlquery.exec())
            break;

        qDebug() << "DATABASE" << "REMOVING" << elem->getRaw();

        queue->dequeue();

        delete elem;
    }

    sqldb->close();
}
