#ifndef UPDATEMOBILE_HPP
#define UPDATEMOBILE_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "inverterdata.hpp"

class UpdateMobile : public QObject
{
        Q_OBJECT
    public:
        explicit UpdateMobile(QObject *parent = 0);
        ~UpdateMobile();

    private:
        QNetworkAccessManager* networkManager;

    public slots:
        void update(InverterData*data);

    private slots:
        void confirm(QNetworkReply* reply);
};

#endif // UPDATEMOBILE_HPP
