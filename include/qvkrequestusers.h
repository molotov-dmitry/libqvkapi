/*!
  \file
  \brief Файл с описанием класса запросов информации о пользователях
*/

#ifndef QVKREQUESTUSERS_H
#define QVKREQUESTUSERS_H

#include "qvkuserinfo.h"
#include "qvkrequest.h"

/*!
 * \brief Класс для выполнения методов API ВКонтакте для работы с данными пользователей
 */
class QVkRequestUsers : public QVkRequest
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса
     * \param[in] token Идентификатор сессии
     * \param[in] parent Родительский объект
     */
    explicit QVkRequestUsers(const QByteArray &token = QByteArray(),
                             QObject *parent = 0);

    /*!
     * \brief Запрос базовой информации о пользователе
     * \param[in] userId Идентификатор пользователя
     */
    void requestBasicUserInfo(unsigned long userId);

    /*!
     * \brief Запрос базовой информации о пользователе
     * \param[in] userIds Перечисленные через запятую идентификаторы пользователей или их короткие имена
     */
    void requestBasicUserInfo(QStringList userIds);

    /*!
     * \brief Запрос полной информации о пользователе
     * \param[in] userId Идентификатор пользователя
     */
    void requestFullUserInfo(unsigned long userId);

    /*!
     * \brief Запрос полной информации о пользователе
     * \param[in] userIds Перечисленные через запятую идентификаторы пользователей или их короткие имена
     */
    void requestFullUserInfo(QStringList userIds);

private slots:

    /*!
     * \brief Получение ответа на запрос API ВКонтакте
     * \param[in] document JSON-схема с ответом сервера
     */
    void receiveBasicUserInfo(QJsonDocument document);

    /*!
     * \brief Получение ответа на запрос API ВКонтакте
     * \param[in] document JSON-схема с ответом сервера
     */
    void receiveFullUserInfo(QJsonDocument document);

signals:

    /*!
     * \brief Базовая информация о пользователе успешно получена
     * \param[out] userInfoList Массив структур базовой информации о пользователях
     */
    void basicUserInfoReceived(QList<VkUserInfoBasic> userInfoList);

    /*!
     * \brief Полная информация о пользователе успешно получена
     * \param[out] userInfoList Массив структур полной информации о пользователях
     */
    void fullUserInfoReceived(QList<VkUserInfoFull> userInfoList);
};

#endif // QVKREQUESTUSERS_H
