#include "vkpagewidget.h"

VkPageWidget::VkPageWidget(QWidget *parent) : QWidget(parent)
{

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

QByteArray VkPageWidget::getPageName() const
{
    return mPageName;
}



