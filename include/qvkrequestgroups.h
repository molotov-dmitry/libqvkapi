#ifndef QVKREQUESTGROUPS_H
#define QVKREQUESTGROUPS_H

#include "qvkrequest.h"
#include "qvkgroupinfo.h"

/*!
 * \brief Класс для выполнения методов API ВКонтакте для работы со списком сообществ
 */
class QVkRequestGroups : public QVkRequest
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса
     * \param[in] token Идентификатор сессии
     * \param[in] parent Родительский объект
     */
    QVkRequestGroups(const QByteArray &token = QByteArray(),
                      QObject *parent = nullptr);

    /*!
     * \brief Запрос списка сообществ пользователя
     * \param[in] userId Идентификатор пользователя
     * \param[in] count Количество сообществ, которое нужно вернуть
     * \param[in] offset Смещение, необходимое для выборки определенного подмножества сообществ
     */
    void requestGroupList(unsigned long userId, unsigned int count = 0, unsigned int offset = 0);

private slots:

    /*!
     * \brief Получение ответа на запрос API ВКонтакте
     * \param[in] document JSON-схема с ответом сервера
     */
    void receiveGroupList(QJsonDocument document);

signals:

    /*!
     * \brief Список сообществ успешно получен
     * \param[out] albumList Массив структур информации о сообществах
     */
    void groupListReceived(QList<VkGroupInfo> groupInfoList);
};

#endif // QVKREQUESTGROUPS_H
