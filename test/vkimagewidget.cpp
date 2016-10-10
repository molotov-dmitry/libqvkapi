#include "vkimagewidget.h"

#include <QPainter>

#include "imagecache.h"

VkImageWidget::VkImageWidget(QWidget *parent) : QWidget(parent)
{
    mImageState = IMAGE_EMPTY;

    mImageType = IMAGE_RECT;
}

void VkImageWidget::setImage(const QString &imageUrl)
{
    mImageState = IMAGE_LOADING;

    ImageCache *imageCache = new ImageCache(this);

    connect(imageCache, SIGNAL(imageLoaded(QImage)), this, SLOT(imageLoaded(QImage)));
    connect(imageCache, SIGNAL(imageLoadFailed(QString)), this, SLOT(imageLoadFailed(QString)));

    imageCache->loadImage(imageUrl);
}

QSize VkImageWidget::imageSize()
{
    return mImage.size();
}

void VkImageWidget::paintEvent(QPaintEvent *e)
{
    if (mImageState == IMAGE_LOADED)
    {
        QPainter p(this);

        p.setRenderHint(QPainter::Antialiasing);

        QBrush brush;
        brush.setTextureImage(mImage.scaled(this->size()));

        p.setBrush(brush);
        p.setPen(Qt::NoPen);

        switch (mImageType)
        {
        case IMAGE_RECT:
        {
            p.drawRect(this->rect());
            break;
        }

        case IMAGE_ROUNDED_RECT:
        {
            p.drawRoundedRect(this->rect(), 15, 15, Qt::RelativeSize);
            break;
        }

        case IMAGE_ELLIPSE:
        {
            p.drawEllipse(this->rect());
            break;
        }

        }

        p.end();
    }
}

VkImageWidget::ImageType VkImageWidget::imageType() const
{
    return mImageType;
}

void VkImageWidget::setImageType(const ImageType &imageType)
{
    mImageType = imageType;

    repaint();
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

