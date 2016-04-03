#include "qvkrequest.h"

#include <QUrl>
#include <QUrlQuery>

#include <QJsonObject>
#include <QJsonParseError>

const QString VK_API_URL = QString("https://api.vk.com");

QVkRequest::QVkRequest(const QByteArray &token,
                       QObject *parent) :
    QObject(parent),
    mApiVersion("5.50"),
    mToken(token)
{
    mManager = new QNetworkAccessManager(this);
    connect(mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getReply(QNetworkReply*)));
}

void QVkRequest::sendRequest(const QString &methodName,
                             const QParam &userParams)
{
    QUrl requestUrl = prepareRequestUrl(methodName, userParams);

    mManager->get(QNetworkRequest(requestUrl));
}

QUrl QVkRequest::prepareRequestUrl(const QString &methodName,
                                   const QParam &userParams)
{
    QString requestUrlString = QString("%1/method/%2").arg(VK_API_URL,
                                                           QString(methodName));

    QUrlQuery requestParam;

    if (!mToken.isEmpty())
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

    QByteArray replyData = reply->readAll();
    QJsonParseError jsonParseError;
    QJsonDocument document = QJsonDocument::fromJson(replyData, &jsonParseError);

    if (jsonParseError.error != QJsonParseError::NoError)
    {
        emit replyFailed(jsonParseError.errorString());
        return;
    }

    if (document.object().contains("error"))
    {
        QString errorMsg = document.object()["error"].toObject()["error_msg"].toString();

        emit replyFailed(errorMsg);
    }

    emit replySuccess(document);
}

