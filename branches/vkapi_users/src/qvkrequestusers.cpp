#include "qvkrequestusers.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

QVkRequestUsers::QVkRequestUsers(const QByteArray &token,
                                 QObject *parent) : QVkRequest(token, parent)
{

}

void QVkRequestUsers::requestBasicUserInfo(unsigned long userId)
{
    QStringList userIds(QString::number(userId));

    requestBasicUserInfo(userIds);
}

void QVkRequestUsers::requestBasicUserInfo(QStringList userIds)
{
    disconnect(this, 0, this, 0);

    QParam paramList;

    QString usersList = userIds.join(',');

    paramList.insert("user_ids", usersList);

    connect(this, SIGNAL(replySuccess(QJsonDocument)),
            this, SLOT(receiveBasicUserInfo(QJsonDocument)));

    sendRequest("users.get", paramList);
}

void QVkRequestUsers::receiveBasicUserInfo(QJsonDocument document)
{
    QList<VkUserInfoBasic> userInfoList;

    //// Iterate trough user list ==============================================

    QJsonArray response = document.object()["response"].toArray();

    foreach (const QJsonValue &value, response)
    {
        QJsonObject object = value.toObject();
        VkUserInfoBasic userInfo;

        //// Get user id and name ----------------------------------------------

        userInfo.id = object["id"].toInt();
        userInfo.firstName = object["first_name"].toString();
        userInfo.lastName = object["last_name"].toString();

        //// Get page status ---------------------------------------------------

        if (object.contains("deactivated"))
        {
            QString pageStatus = object["deactivated"].toString();

            if (pageStatus == QString("deleted"))
                userInfo.pageStatus = VkUser::USER_DELETED;
            else if (pageStatus == QString("banned"))
                userInfo.pageStatus = VkUser::USER_BANNED;
            else
                userInfo.pageStatus = VkUser::USER_ACTIVE;
        }
        else
        {
            userInfo.pageStatus = VkUser::USER_ACTIVE;
        }

        //// Get user visibility -----------------------------------------------

        userInfo.userVisibility = VkUser::USER_VISIBLE;

        if (object.contains("hidden"))
        {
            int userHidden= object["hidden"].toInt();

            if (userHidden)
                userInfo.userVisibility = VkUser::USER_HIDDEN;
        }

        //// Add user info to list ---------------------------------------------

        userInfoList.append(userInfo);
    }

    //// =======================================================================

    emit basicUserInfoReceived(userInfoList);
}

