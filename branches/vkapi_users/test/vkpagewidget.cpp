#include "vkpagewidget.h"

VkPageWidget::VkPageWidget(QWidget *parent) : QWidget(parent)
{

}

void VkPageWidget::setToken(QByteArray token)
{
    mToken = token;
}

void VkPageWidget::updatePage()
{

}

QByteArray VkPageWidget::getPageId() const
{
    return mPageId;
}

