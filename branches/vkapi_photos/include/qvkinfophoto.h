#ifndef QVKINFOPHOTO
#define QVKINFOPHOTO

#include <QString>
#include <QDateTime>

/*!
 * \brief Информация о фотографии
 */
struct VkPhotoInfo
{
    unsigned long       id;             ///< Идентификатор фотографии
    long                albumId;        ///< Идентификатор альбома, в котором находится фотография
    unsigned long       userId;         ///< Идентификатор владельца фотографии

    unsigned int        width;          ///< Ширина фотографии
    unsigned int        height;         ///< Высота фотографии

    QString             photo_75;       ///< URL копии фотографии с максимальным размером 75x75px
    QString             photo_130;      ///< URL копии фотографии с максимальным размером 130x130px
    QString             photo_604;      ///< URL копии фотографии с максимальным размером 604x604px
    QString             photo_807;      ///< URL копии фотографии с максимальным размером 807x807px
    QString             photo_1280;     ///< URL копии фотографии с максимальным размером 1280x1024px
    QString             photo_2560;     ///< URL копии фотографии с максимальным размером 2560x2048px

    QString             text;           ///< Текст описания фотографии

    QDateTime           uploaded;       ///< Дата загрузки фотографии
};

#endif // QVKINFOPHOTO

