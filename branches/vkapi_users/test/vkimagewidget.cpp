#include "vkimagewidget.h"

#include <QPainter>

#include "imagecache.h"

VkImageWidget::VkImageWidget(QWidget *parent) : QWidget(parent)
{
    mImageState = IMAGE_EMPTY;

    mCircleImage = true;
}

void VkImageWidget::setImage(const QString &imageUrl)
{
    mImageState = IMAGE_LOADING;

    ImageCache *imageCache = new ImageCache(this);

    connect(imageCache, SIGNAL(imageLoaded(QImage)), this, SLOT(imageLoaded(QImage)));
    connect(imageCache, SIGNAL(imageLoadFailed(QString)), this, SLOT(imageLoadFailed(QString)));

    imageCache->loadImage(imageUrl);
}

void VkImageWidget::setCircleImage(bool circleImage)
{
    mCircleImage = circleImage;

    repaint();
}

void VkImageWidget::paintEvent(QPaintEvent *e)
{
    if (mImageState == IMAGE_LOADED)
    {
        QPainter p(this);

        p.setRenderHint(QPainter::Antialiasing);

        QBrush brush;
        brush.setTextureImage(mImage);

        p.setBrush(brush);
        p.setPen(Qt::NoPen);

        p.drawEllipse(this->rect());

        p.end();
    }
}

void VkImageWidget::imageLoaded(const QImage &image)
{
    mImage = image;

    mImageState = IMAGE_LOADED;

    repaint();
}

void VkImageWidget::imageLoadFailed(const QString &errorText)
{
    mImageState = IMAGE_ERROR;

    repaint();
}

