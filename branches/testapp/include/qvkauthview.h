#ifndef QVKAUTHORIZEVIEW_H
#define QVKAUTHORIZEVIEW_H

#include <QObject>
#include <QDateTime>

#include <QWebView>

class QVkAuthView : public QObject
{
    Q_OBJECT
public:
    explicit QVkAuthView(QObject *parent = 0);

    ~QVkAuthView();

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

    void authSuccess(const QByteArray& token, const QDateTime &tokenExpire, unsigned int userId);
    void authFailed(const QString &error);
    void authProgress(int progress);

private slots:

    void setProgress(int progress);
    void stageLoaded(bool success);
};

#endif // QVKAUTHORIZEVIEW_H
