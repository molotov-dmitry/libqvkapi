#ifndef QVKAPIUSERS_H
#define QVKAPIUSERS_H

#include <QObject>

#include <QDateTime>

#include <QNetworkReply>

/*!
 * \brief Информация о пользователе
 */
struct VkUser
{
    /*!
     * \brief Статус пользователя
     */
    enum VkUserStatus
    {
        USER_ACTIVE,                ///< Пользователь активен
        USER_DELETED,               ///< Пользователь удалён
        USER_BANNED                 ///< Пользователь заблокирован
    };

    /*!
     * \brief Видимость страницы
     *
     * Возвращается при вызове без access_token, если пользователь установил
     * настройку «Кому в интернете видна моя страница» —
     * «Только пользователям ВКонтакте».
     */
    enum VkUserVisibility
    {
        USER_VISIBLE,               ///< Страница видна всем
        USER_HIDDEN,                ///< Страница видна только зарегистрированным пользователям
    };

    /*!
     * \brief Пол пользователя
     */
    enum VkUserSex
    {
        USER_SEX_NOT_SPECIFIED,     ///< Пол не указан
        USER_FEMALE,                ///< Женский
        USER_MALE                   ///< Мужской
    };

    /*!
     * \brief Онлайн пользователя
     */
    enum VkUserOnline
    {
        USER_OFFLINE,               ///< Пользователь оффлайн
        USER_ONLINE,                ///< Пользователь онлайн
        USER_ONLINE_MOBILE          ///< Пользователь онлайн и использует мобильное приложение
    };

    unsigned int        id;             ///< Идентификатор пользователя
    QString             firstName;      ///< Имя пользователя
    QString             lastName;       ///< Фамилия пользователя

    VkUserStatus        pageStatus;     ///< Статус страницы пользователя
    VkUserVisibility    userVisibility; ///< Видимость страницы

    bool                verified;       ///< Сраница верифицирована
    VkUserSex           userSex;        ///< Пол пользователя

    unsigned char       birthDay;       ///< День рождения
    unsigned char       birthMonth;     ///< Месяц рожения
    unsigned int        birthYear;      ///< Год рождения

    QString             city;           ///< Город
    QString             country;        ///< Страна
    QString             homeTown;       ///< Родной город пользователя

    VkUserOnline        userOnline;     ///< Онлайн пользователя

    QString             mobilePhone;    ///< Номер мобильного телефона
    QString             homePhone;      ///< Дополнительный номер телефона

    QString             statusText;     ///< Статус пользователя

    QDateTime           lastSeen;       ///< Время последнего посещения
};


class QVkApiUsers : public QObject
{
    Q_OBJECT
public:
    explicit QVkApiUsers(QObject *parent = 0);

    /*!
     * \brief Запрос информации о пользователях
     * \param[in] token Идентификатор сессии
     * \param[in] userIdList Список идентификаторов пользователей
     */
    void requestUserInfo(const QByteArray &token,
                         const QList<unsigned int> userIdList);

signals:

private slots:

    void replyUserInfo(QNetworkReply *reply);
};

#endif // QVKAPIUSERS_H
