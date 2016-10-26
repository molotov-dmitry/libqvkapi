#ifndef VKPAGEALBUMS_H
#define VKPAGEALBUMS_H

#include <QAbstractButton>
#include <QTimer>

#include "vkpagewidget.h"

#include "qvkalbuminfo.h"
#include "qvkuserinfo.h"

class VkAlbumThumb : public QObject
{
    Q_OBJECT

public:
    explicit VkAlbumThumb(QAbstractButton* button, const QString &thumbUrl, QObject *parent);

    QAbstractButton *button() const;

private:

    QAbstractButton *mButton;

    QTimer mLoadingAnimationTimer;

    QList<QPixmap> mLoadingAnimationImageList;
    unsigned int mLoadingAnimationCount;

    unsigned int mLoadingAnimationIndex;

private slots:

    void updateLoadingAnimation();

    void imageLoaded(const QImage &image);
    void imageLoadFailed(const QString &errorText);

};

namespace Ui {
class VkPageAlbums;
}

class VkPageAlbums : public VkPageWidget
{
    Q_OBJECT

public:
    explicit VkPageAlbums(QWidget *parent = 0);
    ~VkPageAlbums();

    void setUserId(unsigned int userId);
    void setUserInfo(const VkUserInfoBasic &userInfo);

    virtual QUrl getPageUrl() const;

private slots:

    void albumListReceived(QList<VkAlbumInfo> albumList);
    void userInfoReceived(QList<VkUserInfoBasic> userInfoList);

private:
    Ui::VkPageAlbums *ui;

    unsigned int mUserId;

    QList<VkAlbumThumb*> mAlbumThumbs;

public slots:

    void updateUserInfo();

    virtual void updatePage();

signals:

    void pageLoaded(const QString &pageId, const VkUserInfoBasic &userInfo);
};

#endif // VKPAGEALBUMS_H
