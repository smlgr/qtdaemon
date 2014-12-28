#include <QTimer>

#include "config.hpp"
#include "solarmaxlogger.hpp"
#include "invertercomm.hpp"
#include "inverterdata.hpp"
#include "sqlstorage.hpp"
#include "updatemobile.hpp"

SolarMaxLogger::SolarMaxLogger(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->setInterval(SMLGR_CONFIG_DEFAULT_INTERVAL);

    inv = new InverterComm(this);
    inv->setIp(SMLGR_CONFIG_DEFAULT_INV_ADDR);
    inv->setPort(SMLGR_CONFIG_DEFAULT_INV_PORT);
    inv->setId(SMLGR_CONFIG_DEFAULT_INV_NUM);
    inv->setQuery(SMLGR_CONFIG_DEFAULT_QUERY);

    sql = new SqlStorage(this);
    sql->config(SMLGR_CONFIG_DEFAULT_SQL_ADDR, SMLGR_CONFIG_DEFAULT_SQL_PORT,
                SMLGR_CONFIG_DEFAULT_SQL_USERNAME, SMLGR_CONFIG_DEFAULT_SQL_PASSWORD,
                SMLGR_CONFIG_DEFAULT_SQL_DATABASE);

    mobile = new UpdateMobile(this);

    connect(timer, SIGNAL(timeout()), inv, SLOT(sendNewQuery()));

//    connect(inv, SIGNAL(newResponse(InverterData)), this, SLOT(printData(InverterData)));
    connect(inv, SIGNAL(newResponse(InverterData)), sql, SLOT(addDataIntoQueue(InverterData)));
    connect(inv, SIGNAL(newResponse(InverterData)), mobile, SLOT(update(InverterData)));
}

SolarMaxLogger::~SolarMaxLogger()
{
    delete mobile;

    timer->stop();
    delete timer;

    delete inv;

    sql->stop();
    delete sql;
}

void SolarMaxLogger::printData(InverterData data)
{
    qDebug() << data.getRaw();
}

void SolarMaxLogger::start()
{
    timer->start();
    sql->start();
}

void SolarMaxLogger::stop()
{
    timer->stop();
    sql->stop();
}
