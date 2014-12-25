#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QPair>
#include <QList>
#include <QDebug>

#include "invertercomm.hpp"

InverterComm::InverterComm(QObject *parent) : QObject(parent)
{
    sock = new QTcpSocket();

    connect(sock, SIGNAL(connected()), this, SLOT(writeNewQuery()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(readResponse()));

    running = false;
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

QList<QPair<QString, int> > InverterComm::getResponse() const
{
    return response;
}

void InverterComm::sendNewQuery()
{
    if(running)
        return;

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

    qDebug() << "RECV:" << data;

    parseResponse(data);
}

void InverterComm::parseResponse(QByteArray data)
{
    QString resp(data);

    QStringList frag = resp.split("|");

    response.clear();

    foreach(QString elem, frag[1].mid(4).split(";")) {
        QStringList i = elem.split("=");

        QPair<QString, int> e;
        e.first = i[0];
        e.second = i[1].toInt(nullptr, 16);

        response.append(e);
    }

    emit newline();
}

void InverterComm::closeSocket()
{
    sock->close();

    running = false;
}

void InverterComm::writeNewQuery()
{
    if(sock->state() != QAbstractSocket::ConnectedState)
        return;

    QString output = prepareQuery();
    qDebug() << "SEND:" << output;
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
