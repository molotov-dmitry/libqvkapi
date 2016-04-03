#include "qvkrequest.h"

#include <QUrl>
#include <QUrlQuery>

const QString VK_API_URL = QString("https://api.vk.com");

QVkRequest::QVkRequest(const QByteArray &requestName,
                       const QByteArray &token,
                       QObject *parent) :
    QObject(parent),
    mApiVersion("5.50"),
    mRequestName(requestName),
    mToken(token)
{
    mManager = new QNetworkAccessManager(this);
    connect(mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getReply(QNetworkReply*)));
}

void QVkRequest::sendRequest(const QParam &userParams)
{
    QUrl requestUrl = prepareRequestUrl(userParams);

    mManager->get(QNetworkRequest(requestUrl));
}

QUrl QVkRequest::prepareRequestUrl(const QParam &userParams)
{
    QString requestUrlString = QString("%1/method/%2.get").arg(VK_API_URL,
                                                               QString(mRequestName));

    QUrlQuery requestParam;
    requestParam.addQueryItem("access_token", mToken);
    requestParam.addQueryItem("v", mApiVersion);

    foreach (QString key, userParams.keys())
        requestParam.addQueryItem(key, userParams.value(key));

    QUrl requestUrl(requestUrlString);
    requestUrl.setQuery(requestParam);

    return requestUrl;
}

void QVkRequest::getReply(QNetworkReply *reply)
{
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError)
    {
        emit replyFailed(reply->errorString());
        return;
    }

    QJsonDocument document = QJsonDocument::fromBinaryData(reply->readAll());

    emit replySuccess(document);
}

