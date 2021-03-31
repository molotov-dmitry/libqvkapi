#include "qvkrequestphotos.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>

//// ___________________________________________________________________________
//// ___________________________________________________________________________
//// ___________________________________________________________________________

//// ===========================================================================
//// Конструктор ===============================================================
//// ===========================================================================

QVkRequestPhotos::QVkRequestPhotos(const QByteArray &token, QObject *parent) :
    QVkRequest(token, parent, "5.60")
{

}

//// ===========================================================================
//// Список фотографий пользователя ============================================
//// ===========================================================================

//// ===========================================================================
//// Запрос всех фотографий пользователя ---------------------------------------
//// ===========================================================================

void QVkRequestPhotos::requestUserPhotoList(unsigned long userId, unsigned int count, unsigned int offset)
{
    disconnect(this, 0, this, 0);

    QParam paramList;

    paramList.insert("owner_id", QString::number(userId));

    if (count > 0)
        paramList.insert("count", QString::number(count));

    paramList.insert("offset", QString::number(offset));

    connect(this, SIGNAL(replySuccess(QJsonDocument)),
            this, SLOT(receivePhotoList(QJsonDocument)));

    sendRequest("photos.getAll", paramList);
}

//// ===========================================================================
//// Запрос фотографий из альбома пользователя ---------------------------------
//// ===========================================================================

void QVkRequestPhotos::requestAlbumPhotoList(unsigned long userId, long albumId, unsigned int count, unsigned int offset)
{
    disconnect(this, 0, this, 0);

    QParam paramList;

    paramList.insert("owner_id", QString::number(userId));

    paramList.insert("album_id", QString::number(albumId));

    if (count > 0)
        paramList.insert("count", QString::number(count));

    paramList.insert("offset", QString::number(offset));

    connect(this, SIGNAL(replySuccess(QJsonDocument)),
            this, SLOT(receivePhotoList(QJsonDocument)));

    sendRequest("photos.get", paramList);
}

//// ===========================================================================
//// Обработка ответа ----------------------------------------------------------
//// ===========================================================================

void QVkRequestPhotos::receivePhotoList(QJsonDocument document)
{
    QList<VkPhotoInfo> photoInfoList;

    QJsonObject response = document.object()["response"].toObject();

    //// Get total photo count =================================================

    unsigned long totalPhotoCount = response["count"].toVariant().toULongLong();

    //// Iterate trough album list =============================================

    QJsonArray items = response["items"].toArray();

    foreach (const QJsonValue &value, items)
    {
        QJsonObject object = value.toObject();
        VkPhotoInfo photoInfo;

        //// Get id, owner id, and album id ------------------------------------

        photoInfo.id = object["id"].toVariant().toULongLong();
        photoInfo.userId = object["owner_id"].toVariant().toULongLong();
        photoInfo.albumId = object["album_id"].toVariant().toLongLong();

        //// Get text ----------------------------------------------------------

        if (object.contains("text"))
            photoInfo.text = object["text"].toString();

        //// Get photo URLs ----------------------------------------------------

        if (object.contains("photo_75"))
            photoInfo.photo_75 = object["photo_75"].toString();

        if (object.contains("photo_130"))
            photoInfo.photo_130 = object["photo_130"].toString();

        if (object.contains("photo_604"))
            photoInfo.photo_604 = object["photo_604"].toString();

        if (object.contains("photo_807"))
            photoInfo.photo_807 = object["photo_807"].toString();

        if (object.contains("photo_1280"))
            photoInfo.photo_1280 = object["photo_1280"].toString();

        if (object.contains("photo_2560"))
            photoInfo.photo_2560 = object["photo_2560"].toString();

        //// Get upload date/time ----------------------------------------------

        if (object.contains("date"))
        {
            uint timestamp = object["date"].toVariant().toUInt();
            photoInfo.uploaded = QDateTime::fromTime_t(timestamp);
        }

        //// Add photo info to list --------------------------------------------

        photoInfoList.append(photoInfo);
    }

    //// =======================================================================

    emit photoListReceived(totalPhotoCount, photoInfoList);
}

