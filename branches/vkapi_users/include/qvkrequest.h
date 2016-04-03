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

class QVkRequest : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор класса
     * \param[in] requestName Название запроса
     * \param[in] token Идентификатор сессии
     * \param[in] parent Родительский объект
     */
    explicit QVkRequest(const QByteArray &requestName,
                        const QByteArray &token = QByteArray(),
                        QObject *parent = 0);

    /*!
     * \brief Отправить запрос API Вконтакте
     * \param[in] userParams Дополнительные параметры запроса
     */
    void sendRequest(const QParam &userParams = QParam());

protected:
    QByteArray mApiVersion; ///< Используемая версия API ВКонтакте

private:
    QByteArray mRequestName;///< Название запроса
    QByteArray mToken;      ///< Идентификатор сессии

    QNetworkAccessManager *mManager; ///< Менеджер доступа к сети

    /*!
     * \brief Подготовка URL запроса
     * \param userParams Дополнительные параметры запроса
     * \return URL запроса
     */
    QUrl prepareRequestUrl(const QParam &userParams);

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
