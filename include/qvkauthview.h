#ifndef QVKAUTHORIZEVIEW_H
#define QVKAUTHORIZEVIEW_H

#include <QObject>
#include <QDateTime>

#ifdef DEBUG_LOGIN
#include <QWebView>
#else
#include <QWebPage>
#endif

/*!
 * \brief Класс для выполнения аутентификации ВКонтакте
 */
class QVkAuthView : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса
     * \param[in] parent Родительский объект
     */
    explicit QVkAuthView(QObject *parent = nullptr);

    ~QVkAuthView();

    /*!
     * \brief Выполнение аутентификации
     * \param[in] mAppId Идентификатор приложения
     * \param[in] login Имя пользователя
     * \param[in] password Пароль
     */
    void exec(const QByteArray &mAppId,
              const QString &login,
              const QString &password);

private:

    enum AuthStage
    {
        AUTH_INPUT_LOGIN_PASS,
        AUTH_INSTALL_ALLOW,
        AUTH_RESPONSE
    };

    AuthStage   mAuthStage;

#ifdef DEBUG_LOGIN
    QWebView    *mAuthView;
#else
    QWebPage    *mAuthView;
#endif

    QString     mLogin;
    QString     mPassword;

signals:

//    void continueLoading();

    /*!
     * \brief Успешная аутентификация
     * \param[out] token Идентификатор сессии
     * \param[out] tokenExpire Время истечения срока действия сессии
     * \param[out] userId Идентификатор пользователя
     */
    void authSuccess(const QByteArray& token, const QDateTime &tokenExpire, unsigned int userId);

    /*!
     * \brief Ошибка аутентификации
     * \param[out] error Текст ошибки
     */
    void authFailed(const QString &error);

    /*!
     * \brief Прогресс аутентификации
     * \param[out] progress Процент выполнения аутентификации
     */
    void authProgress(int progress);

private slots:

    void setProgress(int progress);
    void stageLoaded(bool success);
};

#endif // QVKAUTHORIZEVIEW_H
