#ifndef SQLSTORAGE_HPP
#define SQLSTORAGE_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include <QQueue>
#include <QTimer>

#include "inverterdata.hpp"

class SqlStorage : public QObject
{
        Q_OBJECT
    public:
        explicit SqlStorage(QObject *parent = 0);
        ~SqlStorage();

        void selectDbType();
        void config(QString ip, int port, QString username, QString password, QString database);
        void start();
        void stop();

    private:
        QSqlDatabase* sqldb;
        QQueue<InverterData*>* queue;
        QTimer* timer;

    public slots:
        void addDataIntoQueue(InverterData data);

    private slots:
        void copyQueueToDatabase();
};

#endif // SQLSTORAGE_HPP
