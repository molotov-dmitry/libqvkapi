#ifndef QVKAPI_H
#define QVKAPI_H

#include "qvkapi_global.h"

#include <QObject>
#include <QDateTime>

/*!
 * \brief Класс для аутентификации ВКонтакте
 */
class QVKAPISHARED_EXPORT QVkAuth : public QObject
{
    Q_OBJECT
public:
    explicit QVkAuth(QObject *parent = 0);

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
     * \brief Аутентификация
     * \param[in] login Имя пользователя
     * \param[in] password Пароль
     */
    void authenticate(const QString &login = QString(),
                   const QString &password = QString());

private:

    QByteArray mAppId;          ///< Идентификатор приложения

    QByteArray mToken;          ///< Идентификатор сессии
    QDateTime mSessionExpire;   ///< Дата окончания действия сессии

    unsigned int mUserId;       ///< Идентификатор текущего пользователя

signals:

    /*!
     * \brief Успешная аутентификации
     * \param token Идентификатор сессии
     * \param tokenExpire ДАта/время истечения действия сессии
     * \param userId Идентификатор аутентифицированного пользователя
     */
    void authSuccess(const QByteArray &token,
                              const QDateTime &tokenExpire,
                              int userId);

    /*!
     * \brief Ошибка аутентификации
     * \param reason Текст ошибки
     */
    void authFailed(const QString& reason);

    /*!
     * \brief Прогресс аутентификации
     * \param progress Прогресс процесса аутентификации в процентах
     */
    void authProgress(int progress);
};

#endif // QVKAPI_H
