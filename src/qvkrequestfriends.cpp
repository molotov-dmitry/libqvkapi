#include "qvkrequestfriends.h"

#include <QJsonObject>
#include <QJsonArray>

QVkRequestFriends::QVkRequestFriends(const QByteArray& token, QObject* parent)
    : QVkRequest(token, parent, "5.131")
{

}

void QVkRequestFriends::requestFriendList(unsigned long userId, unsigned int count, unsigned int offset)
{
    disconnect(this, nullptr, this, nullptr);

    //// Список параметров =====================================================

    QParam paramList;

    //// Идентификатор пользователя --------------------------------------------

    paramList.insert("user_id", QString::number(userId));

    if (count > 0)
    {
        paramList.insert("count", QString::number(count));
    }

    paramList.insert("offset", QString::number(offset));

    //// Список полей ----------------------------------------------------------

    QStringList fields;
    fields << "nickname";
    fields << "bdate" << "sex" << "online" << "status" << "last_seen" << "verified";
    fields << "photo_50" << "photo_100" << "photo_200_orig" << "photo_200" << "photo_400_orig" << "photo_max" << "photo_max_orig";

    QString fieldsList = fields.join(',');

    paramList.insert("fields", fieldsList);

    //// =======================================================================

    connect(this, SIGNAL(replySuccess(QJsonDocument)),
            this, SLOT(receiveFriendList(QJsonDocument)));

    sendRequest("friends.get", paramList);
}

void QVkRequestFriends::receiveFriendList(QJsonDocument document)
{
    QList<VkUserInfoFull> userInfoList;

    QJsonObject response = document.object()["response"].toObject();
//    int count = response["count"].toInt();
    QJsonArray items = response["items"].toArray();

    foreach (const QJsonValue &value, items)
    {
        QJsonObject object = value.toObject();
        VkUserInfoFull userInfo;

        //// Базовая информаци о пользователе ==================================

        //// Get user id and name ----------------------------------------------

        userInfo.basic.id = object["id"].toVariant().toUInt();
        userInfo.basic.firstName = object["first_name"].toString();
        userInfo.basic.lastName = object["last_name"].toString();

        //// Get page status ---------------------------------------------------

        if (object.contains("deactivated"))
        {
            QString pageStatus = object["deactivated"].toString();

            if (pageStatus == QString("deleted"))
                userInfo.basic.pageStatus = VkUser::USER_DELETED;
            else if (pageStatus == QString("banned"))
                userInfo.basic.pageStatus = VkUser::USER_BANNED;
            else
                userInfo.basic.pageStatus = VkUser::USER_ACTIVE;
        }
        else
        {
            userInfo.basic.pageStatus = VkUser::USER_ACTIVE;
        }

        //// Get user visibility -----------------------------------------------

        userInfo.basic.userVisibility = VkUser::USER_VISIBLE;

        if (object.contains("hidden"))
        {
            int userHidden= object["hidden"].toInt();

            if (userHidden)
                userInfo.basic.userVisibility = VkUser::USER_HIDDEN;
        }

        if (userInfo.basic.pageStatus != VkUser::USER_ACTIVE || userInfo.basic.userVisibility != VkUser::USER_VISIBLE)
        {
            userInfoList.append(userInfo);
            continue;
        }

        //// Информаци о статусе пользователя ==================================

        //// Короткое имя страницы ---------------------------------------------

        if (object.contains("screen_name"))
            userInfo.status.screenName = object["screen_name"].toString();

        //// Дата рождения -----------------------------------------------------

        QString bDate = object["bdate"].toString();
        QStringList bDateList = bDate.split('.');

        if (bDateList.count() > 0)
            userInfo.status.birthDay = bDateList.at(0).toInt();

        if (bDateList.count() > 1)
            userInfo.status.birthMonth = bDateList.at(1).toInt();

        if (bDateList.count() > 2)
            userInfo.status.birthYear = bDateList.at(2).toInt();

        //// Пол пользователя --------------------------------------------------

        userInfo.status.userSex = (VkUser::Sex)object["sex"].toInt();

        //// Онлайн пользователя -----------------------------------------------

        userInfo.status.userOnline = (VkUser::Online)object["online"].toInt();

        if (userInfo.status.userOnline != VkUser::USER_OFFLINE)
        {
            if (object.contains("online_mobile") && object["online_mobile"].toInt() != 0)
                userInfo.status.userOnline = VkUser::USER_ONLINE_MOBILE;
        }

        //// Статус пользователя -----------------------------------------------

        userInfo.status.statusText = object["status"].toString();

        //// Время последнего посещения ----------------------------------------

        if (object.contains("last_seen"))
        {
            QJsonObject lastSeenObject = object["last_seen"].toObject();

            userInfo.status.lastSeen = QDateTime::fromTime_t(lastSeenObject["time"].toVariant().toULongLong());
        }

        //// Сраница верифицирована --------------------------------------------

        userInfo.status.verified = object["verified"].toInt() != 0;

        //// Фотографии профиля ================================================

        userInfo.photo.photo_50 = object["photo_50"].toString();
        userInfo.photo.photo_100 = object["photo_100"].toString();
        userInfo.photo.photo_200_orig = object["photo_200_orig"].toString();
        userInfo.photo.photo_200 = object["photo_200"].toString();
        userInfo.photo.photo_400_orig = object["photo_400_orig"].toString();
        userInfo.photo.photo_max = object["photo_max"].toString();
        userInfo.photo.photo_max_orig = object["photo_max_orig"].toString();

        //// Add user info to list =============================================

        userInfoList.append(userInfo);
    }

    emit friendListReceived(userInfoList);
}
