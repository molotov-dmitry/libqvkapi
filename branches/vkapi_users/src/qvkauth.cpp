#include "qvkauth.h"

#include "qvkauthview.h"

QVkAuth::QVkAuth(QObject *parent) : QObject(parent)
{
}

void QVkAuth::authenticate(const QString &login, const QString &password)
{
    //// Проверка ID приложения ------------------------------------------------

    if (mAppId.isEmpty())
    {
        emit authFailed(QString::fromUtf8("Не указано ID приложения"));
        return;
    }

    //// Очистка старых данных авторизации -------------------------------------

    mToken.clear();
    mSessionExpire = QDateTime();

    mUserId = 0;

    //// Авторизация -----------------------------------------------------------

    QVkAuthView *authView = new QVkAuthView(this);

    connect(authView, SIGNAL(authSuccess(QByteArray,QDateTime,uint)),
            this, SIGNAL(authSuccess(QByteArray,QDateTime,uint)));

    connect(authView, SIGNAL(authFailed(QString)),
            this, SIGNAL(authFailed(QString)));

    connect(authView, SIGNAL(authProgress(int)),
            this, SIGNAL(authProgress(int)));

    authView->exec(mAppId, login, password);
}

void QVkAuth::setAppId(const QByteArray &appId)
{
    mAppId = appId;
}

void QVkAuth::setSession(const QByteArray &token, unsigned int userId)
{
    mToken = token;
    mUserId = userId;
}
