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

};

#endif // QVKPOSTINFO_H
