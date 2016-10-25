#include "qvkrequestusers.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

//// ___________________________________________________________________________
//// ___________________________________________________________________________
//// ___________________________________________________________________________

//// ===========================================================================
//// Конструктор ===============================================================
//// ===========================================================================

QVkRequestUsers::QVkRequestUsers(const QByteArray &token,
                                 QObject *parent) : QVkRequest(token, parent)
{

}

//// ===========================================================================
//// Полная информаци о пользователе ===========================================
//// ===========================================================================

//// ===========================================================================
//// Запрос --------------------------------------------------------------------
//// ===========================================================================

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

//// ===========================================================================
//// Обработка ответа ----------------------------------------------------------
//// ===========================================================================

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

        userInfo.id = object["id"].toVariant().toUInt();
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

//// ===========================================================================
//// Полная информаци о пользователе ===========================================
//// ===========================================================================

//// ===========================================================================
//// Запрос --------------------------------------------------------------------
//// ===========================================================================

void QVkRequestUsers::requestFullUserInfo(unsigned long userId)
{
    QStringList userIds(QString::number(userId));

    requestFullUserInfo(userIds);
}

void QVkRequestUsers::requestFullUserInfo(QStringList userIds)
{
    disconnect(this, 0, this, 0);

    //// Список параметров =====================================================

    QParam paramList;

    //// Список идентификаторов пользователей ----------------------------------

    QString usersList = userIds.join(',');

    paramList.insert("user_ids", usersList);

    //// Список полей ----------------------------------------------------------

    QStringList fields;
    fields << "screen_name";
    fields << "bdate" << "sex" << "online" << "status" << "last_seen" << "verified";
    fields << "city" << "country" << "home_town" << "contacts" << "connections" << "site";
    fields << "counters";
    fields << "photo_50" << "photo_100" << "photo_200_orig" << "photo_200" << "photo_400_orig" << "photo_max" << "photo_max_orig";

    QString fieldsList = fields.join(',');

    paramList.insert("fields", fieldsList);

    //// =======================================================================

    connect(this, SIGNAL(replySuccess(QJsonDocument)),
            this, SLOT(receiveFullUserInfo(QJsonDocument)));

    sendRequest("users.get", paramList);
}

//// ===========================================================================
//// Обработка ответа ----------------------------------------------------------
//// ===========================================================================

void QVkRequestUsers::receiveFullUserInfo(QJsonDocument document)
{
    QList<VkUserInfoFull> userInfoList;

    QJsonArray response = document.object()["response"].toArray();

    foreach (const QJsonValue &value, response)
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

        //// Информация о контактах пользователя ===============================

        //// Город -------------------------------------------------------------

        if (object.contains("city"))
        {
            QJsonObject cityObject = object["city"].toObject();

            userInfo.contacts.city = cityObject["title"].toString();
        }

        //// Страна ------------------------------------------------------------

        if (object.contains("country"))
        {
            QJsonObject countryObject = object["country"].toObject();

            userInfo.contacts.country = countryObject["title"].toString();
        }

        //// Родной город пользователя -----------------------------------------

        if (object.contains("home_town"))
        {
            userInfo.contacts.homeTown = object["home_town"].toString();
        }

        //// Номер мобильного телефона -----------------------------------------

        if (object.contains("mobile_phone"))
            userInfo.contacts.mobilePhone = object["mobile_phone"].toString();


        //// Дополнительный номер телефона -------------------------------------

        if (object.contains("home_phone"))
            userInfo.contacts.homePhone = object["home_phone"].toString();

        //// Сайт --------------------------------------------------------------

        if (object.contains("site"))
            userInfo.contacts.siteUrl = object["site"].toString();

        //// Skype -------------------------------------------------------------

        if (object.contains("skype"))
            userInfo.contacts.skype = object["skype"].toString();

        //// Facebook ----------------------------------------------------------

        if (object.contains("facebook"))
            userInfo.contacts.facebookId = object["facebook"].toString();

        if (object.contains("facebook_name"))
            userInfo.contacts.facebookName = object["facebook_name"].toString();

        //// Twitter -----------------------------------------------------------

        if (object.contains("twitter"))
            userInfo.contacts.twitter = object["twitter"].toString();

        //// Instagram ---------------------------------------------------------

        if (object.contains("instagram"))
            userInfo.contacts.instagram = object["instagram"].toString();


        //// Счётчики ==========================================================

        if (object.contains("counters"))
        {
            QJsonObject countersObject = object["counters"].toObject();

            userInfo.counters.albums = countersObject["albums"].toVariant().toUInt();
            userInfo.counters.videos = countersObject["videos"].toVariant().toUInt();
            userInfo.counters.audios = countersObject["audios"].toVariant().toUInt();
            userInfo.counters.notes = countersObject["notes"].toVariant().toUInt();
            userInfo.counters.photos = countersObject["photos"].toVariant().toUInt();
            userInfo.counters.groups = countersObject["groups"].toVariant().toUInt();
            userInfo.counters.gifts = countersObject["gifts"].toVariant().toUInt();
            userInfo.counters.friends = countersObject["friends"].toVariant().toUInt();
            userInfo.counters.online_friends = countersObject["online_friends"].toVariant().toUInt();
            userInfo.counters.mutual_friends = countersObject["mutual_friends"].toVariant().toUInt();
            userInfo.counters.user_photos = countersObject["user_photos"].toVariant().toUInt();
            userInfo.counters.user_videos = countersObject["user_videos"].toVariant().toUInt();
            userInfo.counters.followers = countersObject["followers"].toVariant().toUInt();
            userInfo.counters.subscriptions = countersObject["subscriptions"].toVariant().toUInt();
            userInfo.counters.pages = countersObject["pages"].toVariant().toUInt();
        }
        else
        {
            memset(&userInfo.counters, 0x00, sizeof(userInfo.counters));
        }

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

    emit fullUserInfoReceived(userInfoList);
}
