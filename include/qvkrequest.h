/*!
  \file
  \brief Файл с описанием класса для запросов API Вконтакте
*/

#ifndef QVKREQUEST_H
#define QVKREQUEST_H

#include <QObject>
#include <QMap>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QJsonDocument>

typedef QMap<QString, QString> QParam;

/*!
 * \brief Класс запроса API ВКонтакте
 */
class QVkRequest : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор класса
     * \param[in] token Идентификатор сессии
     * \param[in] parent Родительский объект
     */
    explicit QVkRequest(const QByteArray &token = QByteArray(),
                        QObject *parent = nullptr,
                        const QByteArray &apiVersion = QByteArray("5.50"));

    /*!
     * \brief Отправка запроса API Вконтакте
     * \param[in] methodName Название запроса
     * \param[in] userParams Дополнительные параметры запроса
     */
    void sendRequest(const QString &methodName,
                     const QParam &userParams = QParam());

protected:
    QByteArray mApiVersion; ///< Используемая версия API ВКонтакте

private:
    QByteArray mToken;      ///< Идентификатор сессии

    QNetworkAccessManager *mManager; ///< Менеджер доступа к сети

    /*!
     * \brief Подготовка URL запроса
     * \param[in] methodName Название запроса
     * \param[in] userParams Дополнительные параметры запроса
     * \return URL запроса
     */
    QUrl prepareRequestUrl(const QString &methodName,
                           const QParam &userParams);

private slots:

    /*!
     * \brief Получение ответа на запрос API ВКонтакте
     * \param[in] reply Ответ на запрос API ВКонтакте
     */
    void getReply(QNetworkReply *reply);

signals:
    /*!
     * \brief Запрос успешно обработан
     * \param reply Ответ на запрос
     */
    void replySuccess(QJsonDocument reply);

    /*!
     * \brief Ошибка обработки запроса
     * \param error Текст ошибки
     */
    void replyFailed(QString error);
};

#endif // QVKREQUEST_H
