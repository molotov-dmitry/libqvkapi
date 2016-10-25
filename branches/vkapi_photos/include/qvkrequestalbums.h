/*!
  \file
  \brief Файл с описанием класса запросов информации о пользователях
*/

#ifndef QVKREQUESTALBUMS_H
#define QVKREQUESTALBUMS_H

#include "qvkalbuminfo.h"
#include "qvkrequest.h"

/*!
 * \brief Класс для выполнения методов API ВКонтакте для работы с альбомами
 */
class QVkRequestAlbums : public QVkRequest
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса
     * \param[in] token Идентификатор сессии
     * \param[in] parent Родительский объект
     */
    explicit QVkRequestAlbums(const QByteArray &token = QByteArray(),
                             QObject *parent = 0);

    /*!
     * \brief Запрос списка альбомов пользователя
     * \param[in] userId Идентификатор пользователя
     * \param[in] count Количество альбомов, которое нужно вернуть
     * \param[in] offset Смещение, необходимое для выборки определенного подмножества альбомов
     */
    void requestAlbumList(unsigned long userId, unsigned int count = 0, unsigned int offset = 0);

private slots:

    /*!
     * \brief Получение ответа на запрос API ВКонтакте
     * \param[in] document JSON-схема с ответом сервера
     */
    void receiveAlbumList(QJsonDocument document);

signals:

    /*!
     * \brief Список альбомов успешно получен
     * \param[out] albumList Массив структур информации об альбомах
     */
    void albumListReceived(QList<VkAlbumInfo> albumInfoList);
};

#endif // QVKREQUESTALBUMS_H
