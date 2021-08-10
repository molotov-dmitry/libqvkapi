#ifndef QVKGROUPINFO_H
#define QVKGROUPINFO_H

#include <QString>
#include <QDateTime>

struct VkGroup
{
    /*!
     * \brief Является ли сообщество закрытым
     */
    enum Access
    {
        GROUP_OPEN,     ///< Открытое
        GROUP_CLOSED,   ///< Закрытое
        GROUP_PRIVATE   ///< Частное
    };

    /*!
     * \brief Статус сообщества
     */
    enum Status
    {
        GROUP_ACTIVE,    ///< Сообщество активно
        GROUP_DELETED,   ///< Сообщество удалено
        GROUP_BANNED     ///< Сообщество заблокировано
    };

    /*!
     * \brief Тип сообщества
     */
    enum Type
    {
        GROUP_GROUP,    ///< Группа
        GROUP_PAGE,     ///< Публичная страница
        GROUP_EVENT,    ///< Мероприятие
    };
};

/*!
 * \brief Информация о сообществе
 */
struct VkGroupInfo
{
    long                id;             ///< Идентификатор сообщества

    QString             name;           ///< Название сообщества
    QString             screenName;     ///< Короткий адрес

    VkGroup::Access     access;         ///< Является ли сообщество закрытым
    VkGroup::Status     status;         ///< Статус сообщества
    VkGroup::Type       type;           ///< Тип сообщества

    QString             photo_50;       ///< URL главной фотографии с размером 50x50px
    QString             photo_100;      ///< URL главной фотографии с размером 100х100px
    QString             photo_200;      ///< URL главной фотографии в максимальном размере
};

#endif // QVKGROUPINFO_H
