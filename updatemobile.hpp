#ifndef UPDATEMOBILE_HPP
#define UPDATEMOBILE_HPP

#include <QObject>
#include <QNetworkReply>

#include "inverterdata.hpp"

class UpdateMobile : public QObject
{
        Q_OBJECT
    public:
        explicit UpdateMobile(QObject *parent = 0);
        ~UpdateMobile();

    public slots:
        void update(InverterData*data);

    private slots:
        void confirm(QNetworkReply* reply);
};

#endif // UPDATEMOBILE_HPP
