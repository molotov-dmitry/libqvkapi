#ifndef QVKREQUESTFRIENDS_H
#define QVKREQUESTFRIENDS_H

#include "qvkrequest.h"
#include "qvkuserinfo.h"

/*!
 * \brief Класс для выполнения методов API ВКонтакте для работы со списком друзей
 */
class QVkRequestFriends : public QVkRequest
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса
     * \param[in] token Идентификатор сессии
     * \param[in] parent Родительский объект
     */
    QVkRequestFriends(const QByteArray &token = QByteArray(),
                      QObject *parent = nullptr);

    /*!
     * \brief Запрос списка друзей пользователя
     * \param[in] userId Идентификатор пользователя
     * \param[in] count Количество друзей, которое нужно вернуть
     * \param[in] offset Смещение, необходимое для выборки определенного подмножества друзей
     */
    void requestFriendList(unsigned long userId, unsigned int count = 0, unsigned int offset = 0);

private slots:

    /*!
     * \brief Получение ответа на запрос API ВКонтакте
     * \param[in] document JSON-схема с ответом сервера
     */
    void receiveFriendList(QJsonDocument document);

signals:

    /*!
     * \brief Список друзей успешно получен
     * \param[out] albumList Массив структур информации о друзьях
     */
    void friendListReceived(QList<VkUserInfoFull> albumInfoList);
};

#endif // QVKREQUESTFRIENDS_H
