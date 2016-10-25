#ifndef ALBUMINFO
#define ALBUMINFO

#include <QString>
#include <QDateTime>

/*!
 * \brief Информация об альбоме
 */
struct VkAlbumInfo
{
    long                id;             ///< Идентификатор альбома
    unsigned long       userId;         ///< Идентификатор владельца альбома

    QString             title;          ///< Название альбома
    QString             description;    ///< Описание альбома
    unsigned long       size;           ///< Количество фотографий в альбоме
    QString             thumbUrl;       ///< Ссылка на изображение обложки альбома

    QDateTime           created;        ///< Дата создания альбома
    QDateTime           updated;        ///< Дата последнего обновления альбома
};


#endif // ALBUMINFO

