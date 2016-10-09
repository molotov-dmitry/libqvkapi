/*!
  \file
  \brief Файл с описанием структур информации о пользователе
*/

#ifndef QVKUSERINFO_H
#define QVKUSERINFO_H

#include <QString>
#include <QDateTime>

/*!
 * \brief Информация о пользователе
 */
struct VkUser
{
    /*!
     * \brief Статус пользователя
     */
    enum Status
    {
        USER_ACTIVE,                    ///< Пользователь активен
        USER_DELETED,                   ///< Пользователь удалён
        USER_BANNED                     ///< Пользователь заблокирован
    };

    /*!
     * \brief Видимость страницы
     *
     * Возвращается при вызове без access_token, если пользователь установил
     * настройку «Кому в интернете видна моя страница» —
     * «Только пользователям ВКонтакте».
     */
    enum Visibility
    {
        USER_VISIBLE,                   ///< Страница видна всем
        USER_HIDDEN,                    ///< Страница видна только зарегистрированным пользователям
    };

    /*!
     * \brief Пол пользователя
     */
    enum Sex
    {
        USER_SEX_NOT_SPECIFIED,         ///< Пол не указан
        USER_FEMALE,                    ///< Женский
        USER_MALE                       ///< Мужской
    };

    /*!
     * \brief Онлайн пользователя
     */
    enum Online
    {
        USER_OFFLINE,                   ///< Пользователь оффлайн
        USER_ONLINE,                    ///< Пользователь онлайн
        USER_ONLINE_MOBILE              ///< Пользователь онлайн и использует мобильное приложение
    };
};

/*!
 * \brief Базовая информация о пользователе
 */
struct VkUserInfoBasic
{
    unsigned int        id;             ///< Идентификатор пользователя
    QString             firstName;      ///< Имя пользователя
    QString             lastName;       ///< Фамилия пользователя

    VkUser::Status      pageStatus;     ///< Статус страницы пользователя
    VkUser::Visibility  userVisibility; ///< Видимость страницы
};

/*!
 * \brief Информация о статусе пользователя
 */
struct VkUserInfoStatus
{
    unsigned char       birthDay;       ///< День рождения
    unsigned char       birthMonth;     ///< Месяц рожения
    unsigned int        birthYear;      ///< Год рождения

    VkUser::Sex         userSex;        ///< Пол пользователя

    VkUser::Online      userOnline;     ///< Онлайн пользователя

    QString             statusText;     ///< Статус пользователя
    QDateTime           lastSeen;       ///< Время последнего посещения

    bool                verified;       ///< Сраница верифицирована
};

/*!
 * \brief Информация о контактах пользователя
 */
struct VkUserInfoContacts
{
    QString             city;           ///< Город
    QString             country;        ///< Страна
    QString             homeTown;       ///< Родной город пользователя

    QString             mobilePhone;    ///< Номер мобильного телефона
    QString             homePhone;      ///< Дополнительный номер телефона
};

/*!
 * \brief Информаци о счётчиках пользователя
 */
struct VkUserInfoCounters
{
    unsigned int        albums;         ///< Количество альбомов
    unsigned int        videos;         ///< Количество видеозаписей
    unsigned int        audios;         ///< Количество аудиозаписей
    unsigned int        notes;          ///< Количество заметок
    unsigned int        photos;         ///< Количество фотографий
    unsigned int        groups;         ///< Количество групп
    unsigned int        gifts;          ///< Количество подарков
    unsigned int        friends;        ///< Количество друзей
    unsigned int        online_friends; ///< Количество друзей онлайн
    unsigned int        mutual_friends; ///< Количество общих друзей
    unsigned int        user_photos;    ///< Количество отметок на фотографиях
    unsigned int        user_videos;    ///< Количество отметок на видеозаписях
    unsigned int        followers;      ///< Количество подписчиков
    unsigned int        subscriptions;  ///< Количество подписок
    unsigned int        pages;          ///< Количество интересных страниц
};


/*!
 * \brief Информация о фотографиях пользователя
 */
struct VkUserInfoPhoto
{
    QString             photo_50;
    QString             photo_100;
    QString             photo_200_orig;
    QString             photo_200;
    QString             photo_400_orig;
    QString             photo_max;
    QString             photo_max_orig;

};

/*!
 * \brief Полная информация о пользователе
 */
struct VkUserInfoFull
{
    VkUserInfoBasic     basic;          ///< Базовая информация о пользователе
    VkUserInfoStatus    status;         ///< Информация о статусе пользователя
    VkUserInfoContacts  contacts;       ///< Информация о контактах пользователя
    VkUserInfoCounters  counters;       ///< Информаци о счётчиках пользователя
    VkUserInfoPhoto     photo;          ///< Информация о фотографиях пользователя
};

#endif // QVKUSERINFO_H
