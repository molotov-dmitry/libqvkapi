#ifndef QVKPOSTINFO_H
#define QVKPOSTINFO_H

#include <QString>
#include <QDateTime>
#include <QList>

/*!
 * \brief Информация о размерах фотографии
 */
struct VkPostPhotoSizeInfo
{
    unsigned int        width;          ///< Ширина фотографии
    unsigned int        height;         ///< Высота фотографии
    QString             url;            ///< URL копии фотографии
};

/*!
 * \brief Информация о фотографии
 */
struct VkPostPhotoInfo
{
    unsigned long       id;             ///< Идентификатор фотографии
    long                albumId;        ///< Идентификатор альбома, в котором находится фотография
    long                userId;         ///< Идентификатор владельца фотографии

    QList<VkPostPhotoSizeInfo> sizes;   ///< размеры фотографии

    QDateTime           uploaded;       ///< Дата загрузки фотографии
};

/*!
 * \brief Информация о видеозиписи
 */
struct VkPostVideoInfo
{
    unsigned long       id;             ///< Идентификатор видеозаписи
    long                ownerId;        ///< Идентификатор владельца видеозаписи

    QString             playerUrl;      ///< URL страницы с плеером, который можно использовать для воспроизведения ролика в браузере

    unsigned int        width;          ///< Ширина видео
    unsigned int        height;         ///< Высота видео

    QString             title;          ///< Название видеозаписи
    QString             description;    ///< Текст описания видеозаписи
    long                duration;       ///< Длительность ролика в секундах

    QDateTime           created;        ///< Дата создания видеозаписи
    QDateTime           uploaded;       ///< Дата добавления видеозаписи пользователем или группой
};

/*!
 * \brief Информация о записи
 */
struct VkPostInfo
{
    unsigned long       id;             ///< Идентификатор записи
    long                ownerId;        ///< Идентификатор владельца стены, на которой размещена запись
    long                fromId;         ///< Идентификатор автора записи


    QString             text;           ///< Текст записи

    QDateTime           date;           ///< Время публикации записи

    QList<VkPostPhotoInfo> photos;      ///< Приложенные фотографии
    QList<VkPostVideoInfo> videos;      ///< Приложенные видеозаписи

};

#endif // QVKPOSTINFO_H
