#include "qvkapiusers.h"

#include "qvkapi.h"

#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>

QVkApiUsers::QVkApiUsers(QObject *parent) : QObject(parent)
{

}

void QVkApiUsers::requestUserInfo(const QByteArray &token,
                                  const QList<unsigned int> userIdList)
{
    QUrl requestUrl("https://api.vk.com/method/users.get");
    QUrlQuery requestParam;

    if (!token.isEmpty())
        requestParam.addQueryItem("access_token", token);

    requestParam.addQueryItem("v", VK_API_VERSION);

    QStringList userIdStrList;

    foreach(unsigned int userId, userIdList)
        userIdStrList.append(QString::number(userId));

    requestParam.addQueryItem("user_ids", userIdStrList.join(','));

    requestUrl.setQuery(requestParam);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyUserInfo(QNetworkReply*)));

    manager->get(QNetworkRequest(requestUrl));

}

void QVkApiUsers::replyUserInfo(QNetworkReply *reply)
{
    QByteArray answer = reply->readAll();

    reply->deleteLater();
}

