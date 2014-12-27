#ifndef INVERTESOCKET_HPP
#define INVERTESOCKET_HPP

#include <QTcpSocket>
#include <QString>
#include <QList>
#include <QPair>

#include "inverterdata.hpp"

class InverterComm: public QObject
{
        Q_OBJECT

    public:
        explicit InverterComm(QObject *parent = 0);
        ~InverterComm();

        QString getQuery() const;
        void setQuery(const QString& value);

        int getPort() const;
        void setPort(int value);

        QString getIp() const;
        void setIp(const QString& value);

        int getId() const;
        void setId(int value);


    private:
        QString ip;
        int port;
        int id;
        QString query;

        bool running;
        QTcpSocket* sock;

        QString prepareQuery();
        bool checkInvParams();
        QString checksum(QString input);
        void parseResponse(QByteArray data);
        void closeSocket();

    signals:
        void newResponse(InverterData*);

    private slots:
        void writeNewQuery();
        void readResponse();
        void resetRunning();

    public slots:
        void sendNewQuery();

};

#endif // INVERTESOCKET_HPP
