#ifndef INVERTERQUERY_HPP
#define INVERTERQUERY_HPP

#include <QObject>
#include <QTimer>
#include <QQueue>

#include "invertercomm.hpp"
#include "inverterdata.hpp"
#include "sqlstorage.hpp"

class SolarMaxLogger : public QObject
{
        Q_OBJECT
    public:
        explicit SolarMaxLogger(QObject *parent = 0);
        ~SolarMaxLogger();

        void start();
        void stop();

    private:
        QTimer* timer;
        InverterComm* inv;
        SqlStorage* sql;

    private slots:
        void printData(InverterData* data);
};

#endif // INVERTERQUERY_HPP
