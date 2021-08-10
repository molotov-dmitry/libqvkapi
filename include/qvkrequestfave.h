#ifndef QVKREQUESTFAVE_H
#define QVKREQUESTFAVE_H

#include "qvkrequest.h"
#include "qvkuserinfo.h"
#include "qvkgroupinfo.h"

typedef QPair<unsigned int, QString> QVkTagInfo;
typedef QList<QVkTagInfo> QVkTagList;

/*!
 * \brief Класс для выполнения методов API ВКонтакте для работы со списком закладок
 */
class QVkRequestFave : public QVkRequest
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса
     * \param[in] token Идентификатор сессии
     * \param[in] parent Родительский объект
     */
    QVkRequestFave(const QByteArray &token = QByteArray(),
                      QObject *parent = nullptr);

    /*!
     * \brief Запрос списка страниц пользователей, добавленных в закладки
     * \param[in] count Количество закладок, которое нужно вернуть
     * \param[in] offset Смещение, необходимое для выборки определенного подмножества закладок
     */
    void requestFaveUserList(unsigned int count = 0, unsigned int offset = 0);

    /*!
     * \brief Запрос списка сообществ, добавленных в закладки
     * \param[in] count Количество закладок, которое нужно вернуть
     * \param[in] offset Смещение, необходимое для выборки определенного подмножества закладок
     */
    void requestFaveGroupList(unsigned int count = 0, unsigned int offset = 0);

private slots:

    /*!
     * \brief Получение ответа на запрос API ВКонтакте
     * \param[in] document JSON-схема с ответом сервера
     */
    void receiveFaveUserList(QJsonDocument document);

    /*!
     * \brief Получение ответа на запрос API ВКонтакте
     * \param[in] document JSON-схема с ответом сервера
     */
    void receiveFaveGroupList(QJsonDocument document);

signals:

    /*!
     * \brief Список страниц пользователей, добавленных в закладки, успешно получен
     * \param[out] faveUserInfoList Список страниц пользователей, добавленных в закладки
     * \param[out] faveUserTagList Тэги для страниц
     */
    void faveUserListReceived(QList<VkUserInfoFull> faveUserInfoList,
                              QMap<long int, QVkTagList> faveUserTagList);

    /*!
     * \brief Список сообществ, добавленных в закладки, успешно получен
     * \param[out] faveInfoList Список сообществ, добавленных в закладки
     * \param[out] faveGroupTagList Тэги для страниц
     */
    void faveGroupListReceived(QList<VkGroupInfo> faveGroupInfoList,
                               QMap<long int, QVkTagList> faveGroupTagList);
};

#endif // QVKREQUESTFAVE_H
