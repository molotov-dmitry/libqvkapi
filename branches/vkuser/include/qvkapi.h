#ifndef QVKAPI_H
#define QVKAPI_H

#include "qvkapi_global.h"

#include <QObject>
#include <QDateTime>

#define VK_API_VERSION "5.50"

/*!
 * \brief Класс для работы с API ВКонтакте
 */
class QVKAPISHARED_EXPORT QVkApi : public QObject
{
    Q_OBJECT
public:
    explicit QVkApi(QObject *parent = 0);

    /*!
     * \brief Установка ID приложения
     * \param[in] ID приложения
     */
    void setAppId(const QByteArray &appId);

    /*!
     * \brief Установка сессии
     * \param[in] token Идентификатор сессии
     * \param[in] userId Идентификатор пользователя
     */
    void setSession(const QByteArray &token, unsigned int userId);

    /*!
     * \brief Авторизация
     * \param[in] login Имя пользователя
     * \param[in] password Пароль
     */
    void authorize(const QString &login = QString(),
                   const QString &password = QString());

private:

    QByteArray mAppId;          ///< Идентификатор приложения

    QByteArray mToken;          ///< Идентификатор сессии
    QDateTime mSessionExpire;   ///< Дата окончания действия сессии

    unsigned int mUserId;       ///< Идентификатор текущего пользователя

signals:

    /*!
     * \brief Успешная авторизация
     * \param token Идентификатор сессии
     * \param tokenExpire ДАта/время истечения действия сессии
     * \param userId Идентификатор авторизованного пользователя
     */
    void authorizationSuccess(const QByteArray &token,
                              const QDateTime &tokenExpire,
                              int userId);

    /*!
     * \brief Ошибка авторизации
     * \param reason Текст ошибки
     */
    void authorizationFailed(const QString& reason);

    /*!
     * \brief Прогресс авторизации
     * \param progress Прогресс процесса авторизации в процентах
     */
    void authorizationProgress(int progress);
};

#endif // QVKAPI_H
