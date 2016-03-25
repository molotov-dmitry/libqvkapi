#include "qvkapi.h"

#include "qvkauthorizeview.h"

QVkApi::QVkApi(QObject *parent) : QObject(parent)
{
}

void QVkApi::authorize(const QString &login, const QString &password)
{
    //// Проверка ID приложения ------------------------------------------------

    if (mAppId.isEmpty())
    {
        emit authorizationFailed(QString::fromUtf8("Не указано ID приложения"));
        return;
    }

    //// Очистка старых данных авторизации -------------------------------------

    mToken.clear();
    mSessionExpire = QDateTime();

    mUserId = 0;

    //// Авторизация -----------------------------------------------------------

    QVkAuthorizeView *authView = new QVkAuthorizeView(this);

    connect(authView, SIGNAL(authorizeSuccess(QByteArray,QDateTime,int)),
            this, SIGNAL(authorizationSuccess(QByteArray,QDateTime,int)));

    connect(authView, SIGNAL(authorizeFailed(QString)),
            this, SIGNAL(authorizationFailed(QString)));

    connect(authView, SIGNAL(authorizeProgress(int)),
            this, SIGNAL(authorizationProgress(int)));

    authView->exec(mAppId, login, password);
}

void QVkApi::setAppId(const QByteArray &appId)
{
    mAppId = appId;
}

void QVkApi::setSession(const QByteArray &token, unsigned int userId)
{
    mToken = token;
    mUserId = userId;
}
