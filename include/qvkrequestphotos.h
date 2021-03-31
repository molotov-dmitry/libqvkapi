/*!
  \file
  \brief Файл с описанием класса запросов информации о фотографиях
*/

#ifndef QVKREQUESTALBUMPHOTOS_H
#define QVKREQUESTALBUMPHOTOS_H

#include "qvkrequest.h"
#include "qvkinfophoto.h"

/*!
 * \brief Класс для получения списка фотографий
 */
class QVkRequestPhotos : public QVkRequest
{
    Q_OBJECT
public:

    /*!
     * \brief Конструктор класса
     * \param[in] token Идентификатор сессии
     * \param[in] parent Родительский объект
     */
    explicit QVkRequestPhotos(const QByteArray &token, QObject *parent = nullptr);

    /*!
     * \brief Запрос списка всех фотографий пользователя
     * \param[in] userId Идентификатор пользователя
     * \param[in] count Количество фотографий, которое нужно вернуть
     * \param[in] offset Смещение, необходимое для выборки определенного подмножества фотографий
     */
    void requestUserPhotoList(unsigned long userId, unsigned int count = 0, unsigned int offset = 0);

    /*!
     * \brief Запрос списка фотографий из альбома пользователя
     * \param[in] userId Идентификатор пользователя
     * \param[in] userId Идентификатор альбома
     * \param[in] count Количество фотографий, которое нужно вернуть
     * \param[in] offset Смещение, необходимое для выборки определенного подмножества фотографий
     */
    void requestAlbumPhotoList(unsigned long userId, long albumId, unsigned int count = 0, unsigned int offset = 0);

private slots:

    /*!
     * \brief Получение ответа на запрос API ВКонтакте
     * \param[in] document JSON-схема с ответом сервера
     */
    void receivePhotoList(QJsonDocument document);

signals:

    /*!
     * \brief Список фотографий успешно получен
     * \param[out] photoInfoList Массив структур информации о фотографиях
     */
    void photoListReceived(unsigned long photoCount, QList<VkPhotoInfo> photoInfoList);
};

#endif // QVKREQUESTALBUMPHOTOS_H
