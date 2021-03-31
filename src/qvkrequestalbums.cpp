#include "qvkrequestalbums.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

//// ___________________________________________________________________________
//// ___________________________________________________________________________
//// ___________________________________________________________________________

//// ===========================================================================
//// Конструктор ===============================================================
//// ===========================================================================

QVkRequestAlbums::QVkRequestAlbums(const QByteArray &token,
                                   QObject *parent) : QVkRequest(token, parent)
{

}

//// ===========================================================================
//// Список альбомов пользователя ==============================================
//// ===========================================================================

//// ===========================================================================
//// Запрос --------------------------------------------------------------------
//// ===========================================================================

void QVkRequestAlbums::requestAlbumList(unsigned long userId, unsigned int count, unsigned int offset)
{
    disconnect(this, 0, this, 0);

    QParam paramList;

    paramList.insert("owner_id", QString::number(userId));
    paramList.insert("need_system", QString::number(true));
    paramList.insert("need_covers", QString::number(true));
    paramList.insert("count", QString::number(count));
    paramList.insert("offset", QString::number(offset));

    connect(this, SIGNAL(replySuccess(QJsonDocument)),
            this, SLOT(receiveAlbumList(QJsonDocument)));

    sendRequest("photos.getAlbums", paramList);
}

//// ===========================================================================
//// Обработка ответа ----------------------------------------------------------
//// ===========================================================================

void QVkRequestAlbums::receiveAlbumList(QJsonDocument document)
{
    QList<VkAlbumInfo> albumInfoList;

    QJsonObject response = document.object()["response"].toObject();

    //// Iterate trough album list =============================================

    QJsonArray items = response["items"].toArray();

    foreach (const QJsonValue &value, items)
    {
        QJsonObject object = value.toObject();
        VkAlbumInfo albumInfo;

        //// Get id and owner id -----------------------------------------------

        albumInfo.id = object["id"].toVariant().toULongLong();
        albumInfo.userId = object["owner_id"].toVariant().toULongLong();

        //// Get title and description -----------------------------------------

        albumInfo.title = object["title"].toString();

        if (object.contains("description"))
            albumInfo.description = object["description"].toString();

        //// Get photos count --------------------------------------------------

        albumInfo.size = object["size"].toVariant().toULongLong();

        //// Get thumb URL -----------------------------------------------------

        albumInfo.thumbUrl = object["thumb_src"].toString();

        //// Create and last update date/time ----------------------------------

        if (object.contains("created"))
        {
            uint timestamp = object["created"].toVariant().toUInt();
            albumInfo.created = QDateTime::fromTime_t(timestamp);
        }

        if (object.contains("updated"))
        {
            uint timestamp = object["updated"].toVariant().toUInt();
            albumInfo.updated = QDateTime::fromTime_t(timestamp);
        }

        //// Add album info to list --------------------------------------------

        albumInfoList.append(albumInfo);
    }

    //// =======================================================================

    emit albumListReceived(albumInfoList);
}

