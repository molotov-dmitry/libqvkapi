#include "qvkauthview.h"

#include <QEventLoop>

#include <QUrlQuery>
#include <QUrl>
#include <QWebElement>
#include <QWebFrame>

const int AUTH_STAGE_COUNT = 3;

QVkAuthView::QVkAuthView(QObject *parent) : QObject(parent)
{
    mAuthView = new QWebView(0);

    mAuthView->settings()->setAttribute(QWebSettings::AutoLoadImages, false);

    //    mAuthView->show();
}

QVkAuthView::~QVkAuthView()
{
    if (mAuthView)
        delete mAuthView;
}

void QVkAuthView::exec(const QByteArray &mAppId, const QString &login, const QString &password)
{   
    //// Reconnect signals -----------------------------------------------------

    disconnect(mAuthView, 0, this, 0);
    mAuthView->stop();

    connect(mAuthView, SIGNAL(loadProgress(int)), this, SLOT(setProgress(int)));
    connect(mAuthView, SIGNAL(loadFinished(bool)), this, SLOT(stageLoaded(bool)));

    //// Set login and password ------------------------------------------------

    if (login.isEmpty())
    {
        emit authFailed(QString::fromUtf8("Не введено имя пользователя"));
        return;
    }

    if (password.isEmpty())
    {
        emit authFailed(QString::fromUtf8("Не введён пароль"));
        return;
    }

    mLogin = login;
    mPassword = password;

    //// Prepare query ---------------------------------------------------------

    QUrlQuery urlQuery;

    QString appId = QString(mAppId);

    urlQuery.addQueryItem("client_id", appId);
    urlQuery.addQueryItem("scope", "notify,friends,photos,status");
    urlQuery.addQueryItem("display", "popup");
    urlQuery.addQueryItem("type", "browser");
    urlQuery.addQueryItem("v", "5.50");
    urlQuery.addQueryItem("response_type", "token");

    QUrl url("https://oauth.vk.com/authorize");

    url.setQuery(urlQuery);

    //// Set stage -------------------------------------------------------------

    mAuthStage = AUTH_INPUT_LOGIN_PASS;

    //// Start loading ---------------------------------------------------------

    mAuthView->load(url);
}

void QVkAuthView::setProgress(int progress)
{
    int totalProgress = (100 * (int)mAuthStage + progress) / AUTH_STAGE_COUNT;

    if (totalProgress > 100)
        totalProgress = 0;

    emit authProgress(totalProgress);
}

void QVkAuthView::stageLoaded(bool success)
{
    //// Проверка успешной загрузки страницы -----------------------------------

    if (!success)
    {
        emit authFailed(QString::fromUtf8("Ошибка загрузки страницы"));

        return;
    }

    //// -----------------------------------------------------------------------

    switch (mAuthStage)
    {

    //// Страница для ввода логина и пароля ------------------------------------

    case AUTH_INPUT_LOGIN_PASS:
    {
        QWebFrame *authFrame = mAuthView->page()->currentFrame();

        if (authFrame)
        {
            QWebElement editEmail = authFrame->findFirstElement("input[type=text][name=email]");
            QWebElement editPass = authFrame->findFirstElement("input[type=password][name=pass]");
            QWebElement btnSubmit = authFrame->findFirstElement("button[id=install_allow]");

            bool btnIsOk = !btnSubmit.isNull();
            bool emailIsOk = !editEmail.isNull();
            bool passIsOk = !editPass.isNull();

            if (!btnIsOk || !emailIsOk || !passIsOk)
            {
                emit authFailed(QString::fromUtf8("Ошибка страницы авторизации"));
                return;
            }

            mAuthStage = AUTH_INSTALL_ALLOW;

            editEmail.setAttribute("value", mLogin);
            editPass.setAttribute("value", mPassword);
            btnSubmit.evaluateJavaScript("this.click();");

        }
        else
        {
            emit authFailed(QString::fromUtf8("Ошибка страницы авторизации"));
            return;
        }

        return;
    }

    case AUTH_INSTALL_ALLOW:
    {
        QWebFrame *authFrame = mAuthView->page()->currentFrame();

        if (authFrame)
        {
            QWebElement errorMessage = authFrame->findFirstElement("div[class=oauth_error]");

            bool haveError = !errorMessage.isNull();

            if (haveError)
            {
                QString errorText = errorMessage.toPlainText();
                emit authFailed(errorText);
                return;
            }

            QWebElement btnSubmit = authFrame->findFirstElement("button[id=install_allow]");

            bool btnIsOk = !btnSubmit.isNull();

            if (!btnIsOk)
            {
                btnSubmit = authFrame->findFirstElement("button[class=\"flat_button fl_r button_indent\"]");
                btnIsOk = !btnSubmit.isNull();
            }

            if (!btnIsOk)
            {
                btnSubmit = authFrame->findFirstElement("button[textContent=Разрешить]");
                btnIsOk = !btnSubmit.isNull();
            }

            if (!btnIsOk)
            {
                btnSubmit = authFrame->findFirstElement("button[textContent=Разрешить]");
                btnIsOk = !btnSubmit.isNull();
            }

            if (!btnIsOk)
            {
                emit authFailed(QString::fromUtf8("Ошибка страницы авторизации"));
                return;
            }

            mAuthStage = AUTH_RESPONSE;

            btnSubmit.evaluateJavaScript("this.click();");
        }

        return;
    }

        //// Проверка ответа сервера авторизации -------------------------------

    case AUTH_RESPONSE:
    {
        QString urlString = mAuthView->url().toString().replace("#", "?");

        QUrlQuery responseUrl = QUrlQuery(QUrl(urlString));

        QString tokenResponce = responseUrl.queryItemValue("access_token");
        QString expiresInResponce = responseUrl.queryItemValue("expires_in");
        QString userIdResponce = responseUrl.queryItemValue("user_id");

        bool expiresInOk;
        int expiresIn = expiresInResponce.toInt(&expiresInOk);

        bool userIdOk;
        unsigned int userId = userIdResponce.toUInt(&userIdOk);

        if (tokenResponce.isEmpty() || !expiresInOk || !userIdOk)
        {
            QString error = responseUrl.queryItemValue("error_description");

            if (error.isEmpty())
                emit authFailed(QString::fromUtf8("Ошибка ответа сервера авторизации"));
            else
                emit authFailed(error);

            return;
        }

        emit authSuccess(tokenResponce.toLocal8Bit(),
                         QDateTime::currentDateTime().addSecs(expiresIn),
                         userId);

        return;
    }


    }
}
