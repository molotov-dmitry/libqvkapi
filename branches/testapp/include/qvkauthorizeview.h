#ifndef QVKAUTHORIZEVIEW_H
#define QVKAUTHORIZEVIEW_H

#include <QObject>
#include <QDateTime>

#include <QWebView>

class QVkAuthorizeView : public QObject
{
    Q_OBJECT
public:
    explicit QVkAuthorizeView(QObject *parent = 0);

    ~QVkAuthorizeView();

    void exec(const QByteArray &mAppId,
              const QString &login,
              const QString &password);

private:

    int     mAuthStage;

    QWebView *mAuthView;

    QString mLogin;
    QString mPassword;

signals:

    void continueLoading();

    void authorizeSuccess(const QByteArray& token, const QDateTime &tokenExpire, int userId);
    void authorizeFailed(const QString &error);
    void authorizeProgress(int progress);

private slots:

    void setProgress(int progress);
    void stageLoaded(bool success);
};

#endif // QVKAUTHORIZEVIEW_H
