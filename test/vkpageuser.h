#ifndef WIDGETUSERINFO_H
#define WIDGETUSERINFO_H

#include "vkpagewidget.h"

#include "qvkuserinfo.h"

namespace Ui {
class VkPageUser;
}

class VkPageUser : public VkPageWidget
{
    Q_OBJECT

public:
    explicit VkPageUser(QWidget *parent = 0);
    ~VkPageUser();

    void setUserInfo(unsigned int userId);
    void setUserInfo(const VkUserInfoFull &userInfo);

private:
    Ui::VkPageUser *ui;

    unsigned int mId;

private slots:

    void userInfoReceived(QList<VkUserInfoFull> userInfoList);

    void showError(const QString &errorText);

public slots:

    virtual void updatePage();
};

#endif // WIDGETUSERINFO_H
