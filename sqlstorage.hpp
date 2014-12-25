#ifndef SQLSTORAGE_HPP
#define SQLSTORAGE_HPP

#include <QObject>
#include <QSqlDatabase>
#include <QString>

class SqlStorage : public QObject
{
        Q_OBJECT
    public:
        explicit SqlStorage(QObject *parent = 0);
        ~SqlStorage();

        void selectDbType(QString type);
        void dbConnect(QString ip, int port, QString username, QString password, QString database);
        bool isConnected();

    private:
        QSqlDatabase* sqldb;


    signals:

    public slots:
};

#endif // SQLSTORAGE_HPP
