#include <QTimer>

#include "config.hpp"
#include "solarmaxlogger.hpp"
#include "invertercomm.hpp"
#include "sqlstorage.hpp"

SolarMaxLogger::SolarMaxLogger(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->setInterval(SMLGR_CONFIG_DEFAULT_INTERVAL);

    inv = new InverterComm();
    inv->setIp(SMLGR_CONFIG_DEFAULT_INV_ADDR);
    inv->setPort(SMLGR_CONFIG_DEFAULT_INV_PORT);
    inv->setId(SMLGR_CONFIG_DEFAULT_INV_NUM);
    inv->setQuery(SMLGR_CONFIG_DEFAULT_QUERY);

    sql = new SqlStorage(this);
    sql->selectDbType(SMLGR_CONFIG_DEFAULT_SQL_TYPE);
    sql->dbConnect(SMLGR_CONFIG_DEFAULT_SQL_ADDR, SMLGR_CONFIG_DEFAULT_SQL_PORT,
                   SMLGR_CONFIG_DEFAULT_SQL_USERNAME, SMLGR_CONFIG_DEFAULT_SQL_PASSWORD,
                   SMLGR_CONFIG_DEFAULT_SQL_DATABASE);

    connect(timer, SIGNAL(timeout()), inv, SLOT(sendNewQuery()));
    connect(inv, SIGNAL(newline()), this, SLOT(printData()));
}

SolarMaxLogger::~SolarMaxLogger()
{

}

void SolarMaxLogger::printData()
{
    qDebug() << inv->getResponse();
}

void SolarMaxLogger::start()
{
    timer->start();
}

void SolarMaxLogger::stop()
{
    timer->stop();
}
