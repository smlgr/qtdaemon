#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QPair>
#include <QList>

#include "invertercomm.hpp"
#include "inverterdata.hpp"

InverterComm::InverterComm(QObject *parent) : QObject(parent)
{
    sock = new QTcpSocket();

    connect(sock, SIGNAL(connected()), this, SLOT(writeNewQuery()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(readResponse()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(resetRunning()));

    running = false;

    response = nullptr;
}

InverterComm::~InverterComm()
{

}

QString InverterComm::getQuery() const
{
    return query;
}

void InverterComm::setQuery(const QString& value)
{
    query = value;
}

int InverterComm::getPort() const
{
    return port;
}

void InverterComm::setPort(int value)
{
    port = value;
}

QString InverterComm::getIp() const
{
    return ip;
}

void InverterComm::setIp(const QString& value)
{
    ip = value;
}
int InverterComm::getId() const
{
    return id;
}

void InverterComm::setId(int value)
{
    id = value;
}

InverterData* InverterComm::getResponse() const
{
    return response;
}

void InverterComm::sendNewQuery()
{
    if(running)
        closeSocket();

    if(!checkInvParams())
        return;

    running = true;

    sock->connectToHost(ip, port);

    if(!sock->waitForConnected(10000))
        closeSocket();
}

void InverterComm::readResponse()
{
    QByteArray data = sock->readAll();
    closeSocket();

    parseResponse(data);
}

void InverterComm::parseResponse(QByteArray data)
{
    if(response != nullptr)
        delete response;

    response = new InverterData();

    response->setDatetime(QDateTime::currentDateTime());

    QString resp(data);
    response->setRaw(resp);

    QStringList frag = resp.split("|");

    foreach(QString elem, frag[1].mid(3).split(";")) {
        QStringList i = elem.split("=");

        int val = i[1].toInt(nullptr, 16);

        if(i[0] == "UDC")
            response->setUdc((float) val / 10);

        if(i[0] == "IDC")
            response->setIdc((float) val / 100);

        if(i[0] == "UL1")
            response->setUl1((float) val / 10);

        if(i[0] == "IL1")
            response->setIl1((float) val / 100);

        if(i[0] == "PAC")
            response->setPac((float) val / 2);

        if(i[0] == "PRL")
            response->setPrl(val);

        if(i[0] == "TKK")
            response->setTkk(val);

        if(i[0] == "TNF")
            response->setTnf((float) val / 100);

        if(i[0] == "KDY")
            response->setKdy((float) val / 10);

        if(i[0] == "KLD")
            response->setKld((float) val / 10);
    }

    emit newResponse(response);
}

void InverterComm::closeSocket()
{
    sock->close();
}

void InverterComm::resetRunning()
{
    running = false;
}

void InverterComm::writeNewQuery()
{
    if(sock->state() != QAbstractSocket::ConnectedState)
        return;

    QString output = prepareQuery();

    sock->write(output.toUtf8());
}

QString InverterComm::prepareQuery()
{
    QString str_inv;
    str_inv.sprintf("%02X", id);

    QString str_len;
    str_len.sprintf("%02X", 13 + query.length() + 6);

    QString format;
    format = "FB;%1;%2|64:%3|";

    QString tmp;
    tmp = format.arg(str_inv, str_len, query);

    QString ret = "{" + tmp + checksum(tmp) + "}";

    return ret;
}

QString InverterComm::checksum(QString input)
{
    if(input == nullptr)
        return nullptr;

    if(input.length() == 0)
        return "";

    int sum = 0;

    foreach(QChar c, input) {
        sum += c.toAscii();
        sum %= 0xffff;
    }

    QString ret;

    return ret.sprintf("%04X", sum);
}

bool InverterComm::checkInvParams()
{
    if((ip == nullptr) || (ip.length() == 0))
        return false;

    if((port < 1) || (port > 65535))
        return false;

    if((id < 1) || (id > 255))
        return false;

    if((query == nullptr) || (query.length() == 0))
        return false;

    return true;
}
