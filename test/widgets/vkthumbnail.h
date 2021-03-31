#ifndef VKTHUMBNAIL_H
#define VKTHUMBNAIL_H

#include <QObject>
#include <QTimer>
#include <QIcon>

class VkThumbnail : public QObject
{
    Q_OBJECT
public:
    explicit VkThumbnail(void *item, unsigned int imageSize, QObject *parent = 0);

    void load(const QString &thumbUrl);

    void unsetItem();

protected:

    virtual void setIcon(const QIcon &icon) = 0;

    void* mItem;

private:

    unsigned int mImageSize;

    QTimer mLoadingAnimationTimer;

    QList<QPixmap> mLoadingAnimationImageList;
    unsigned int mLoadingAnimationCount;

    unsigned int mLoadingAnimationIndex;

    QIcon mErrorIcon;

private slots:

    void unsetItem(QObject *object);

    void updateLoadingAnimation();

    void imageLoaded(const QImage &image);
    void imageLoadFailed(const QString &errorText);
};

#endif // VKTHUMBNAIL_H
