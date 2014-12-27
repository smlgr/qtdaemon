#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

#include "updatemobile.hpp"
#include "inverterdata.hpp"

UpdateMobile::UpdateMobile(QObject *parent) : QObject(parent)
{

}

UpdateMobile::~UpdateMobile()
{

}

void UpdateMobile::update(InverterData* data)
{
    QUrl url;
    url.setUrl("http://smlgr.thehellnet.org/api/send.php");

    QUrl params;
    params.addQueryItem("UL1", QString::number(data->getUl1()));
    params.addQueryItem("PAC", QString::number(data->getPac()));
    params.addQueryItem("TKK", QString::number(data->getTkk()));
    params.addQueryItem("TNF", QString::number(data->getTnf()));
    params.addQueryItem("KDY", QString::number(data->getKdy()));

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(confirm(QNetworkReply*)));

    networkManager->post(request, params.encodedQuery());
}

void UpdateMobile::confirm(QNetworkReply* reply)
{
    qDebug() << reply->readAll();

    delete networkManager;
}
