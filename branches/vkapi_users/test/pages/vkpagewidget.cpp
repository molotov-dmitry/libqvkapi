#include "vkpagewidget.h"

#include <QHBoxLayout>

VkPageWidget::VkPageWidget(QWidget *parent) :
    QWidget(parent),
    mPageContent(0),
    mLoadingAnimationCount(0),
    mLoadingAnimationIndex(0),
    mPageStatus(PAGE_LOADING)
{
    //// Loading widget ========================================================

    mPageLoading = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(mPageLoading);

    //// Left spacer -----------------------------------------------------------

    QWidget *widgetLeft = new QWidget(mPageLoading);
    widgetLeft->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(widgetLeft);

    //// Animation widget ------------------------------------------------------

    mLoadingAnimation = new QLabel(mPageLoading);
    layout->addWidget(mLoadingAnimation);

    //// Loading text widget ---------------------------------------------------

    layout->addWidget(new QLabel("Загрузка страницы...", mPageLoading));

    //// Right spacer ----------------------------------------------------------

    QWidget *widgetRight = new QWidget(mPageLoading);
    widgetRight->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    layout->addWidget(widgetRight);

    //// Animation -------------------------------------------------------------

    mLoadingAnimationTimer.setInterval(50);
    connect(&mLoadingAnimationTimer, SIGNAL(timeout()), this, SLOT(updateAnimation()));

    QImage anim = QImage(":/anim/process-working.png");

    int animCols = 8;
    int animSize = anim.width() / animCols;
    int animRows = anim.height() / animSize;

    for (int y = 0; y < animRows; ++y)
    {
        for (int x = 0; x < animCols; ++x)
        {
            if (y == 0 && x == 0)
                continue;

            QPixmap pixmap = QPixmap::fromImage(anim.copy(x * animSize, y * animSize, animSize, animSize));

            mLoadingAnimationImageList.append(pixmap);
        }
    }

    mLoadingAnimationCount = animRows * animCols - 1;

    mLoadingAnimation->setMinimumSize(animSize, animSize);

    //// Error text widget =====================================================

    mPageErrorText = new QLabel(this);

    QPalette errorPalette;
    errorPalette.setColor(QPalette::WindowText, QColor(200, 0, 0));
    mPageErrorText->setPalette(errorPalette);

    mPageErrorText->setAlignment(Qt::AlignCenter);

    //// Set page status =======================================================

    setPageStatus(PAGE_LOADING);
}

void VkPageWidget::setToken(QByteArray token)
{
    mToken = token;
}

bool VkPageWidget::isThisPage(const QString &pageName)
{
    bool isNumber;      ///< argument is number, like "0"
    bool isIdNumber;    ///< argument is page id, like "id0"

    if (pageName.isEmpty())
        return false;

    pageName.toUInt(&isNumber);

    pageName.mid(2).toUInt(&isIdNumber);
    isIdNumber = isIdNumber && pageName.startsWith("id");

    if (isNumber)
        return (mPageId == QString("id") + pageName);
    else if (isIdNumber)
        return (mPageId == pageName);
    else
        return (mPageName == pageName);
}

QByteArray VkPageWidget::getPageId() const
{
    return mPageId;
}

void VkPageWidget::updatePage()
{

}

void VkPageWidget::setError(const QString &errorText)
{
    mPageErrorText->setText(errorText);

    setPageStatus(PAGE_ERROR);
}

void VkPageWidget::updateAnimation()
{
    mLoadingAnimation->setPixmap(mLoadingAnimationImageList.at(mLoadingAnimationIndex));

    mLoadingAnimationIndex = (mLoadingAnimationIndex + 1) % mLoadingAnimationCount;
}

QByteArray VkPageWidget::getPageName() const
{
    return mPageName;
}

void VkPageWidget::setPageContent(QWidget *pageContent, QBoxLayout *mainLayout)
{
    mPageContent = pageContent;
    mainLayout->addWidget(mPageLoading);
    mainLayout->addWidget(mPageErrorText);

    setPageStatus(mPageStatus);
}

void VkPageWidget::setPageStatus(const PageStatus &pageStatus)
{
    mPageStatus = pageStatus;

    switch (mPageStatus)
    {
    case PAGE_LOADING:

        if (mPageContent)
            mPageContent->hide();
        mPageLoading->show();
        mPageErrorText->hide();

        mLoadingAnimationTimer.start();

        break;


    case PAGE_LOADED:

        if (mPageContent)
            mPageContent->show();

        mPageLoading->hide();
        mPageErrorText->hide();

        mLoadingAnimationTimer.stop();

        break;


    case PAGE_ERROR:
        if (mPageContent)
            mPageContent->hide();
        mPageLoading->hide();
        mPageErrorText->show();

        mLoadingAnimationTimer.stop();

        break;

    }
}



