#ifndef VKIMAGEWIDGET_H
#define VKIMAGEWIDGET_H

#include <QWidget>
#include <QPaintEvent>

#include <QImage>

class VkImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VkImageWidget(QWidget *parent = 0);

    void setImage(const QString &imageUrl);

    void setCircleImage(bool circleImage);

private:

    enum ImageState
    {
        IMAGE_EMPTY,
        IMAGE_LOADING,
        IMAGE_LOADED,
        IMAGE_ERROR
    };

    void paintEvent(QPaintEvent *e);

    QImage mImage;
    ImageState mImageState;

    bool mCircleImage;

private slots:

    void imageLoaded(const QImage &image);
    void imageLoadFailed(const QString &errorText);
};

#endif // VKIMAGEWIDGET_H
