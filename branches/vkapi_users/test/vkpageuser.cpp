#include "vkpageuser.h"
#include "ui_vkpageuser.h"

#include <QPalette>
#include <QDateTime>

#include <qvkrequestusers.h>

VkPageUser::VkPageUser(QWidget *parent) :
    VkPageWidget(parent),
    ui(new Ui::VkPageUser)
{
    ui->setupUi(this);

    QPalette labelPalette;
    QColor labelColor = labelPalette.color(QPalette::WindowText);
    labelColor.setAlphaF(0.75);

    labelPalette.setColor(QPalette::WindowText, labelColor);

    ui->labelBirthDate->setPalette(labelPalette);
    ui->labelCountry->setPalette(labelPalette);
    ui->labelCity->setPalette(labelPalette);
    ui->labelHomeTown->setPalette(labelPalette);
    ui->labelMobilePhone->setPalette(labelPalette);
    ui->labelOtherPhone->setPalette(labelPalette);

    ui->imageProfile->setImageType(VkImageWidget::IMAGE_ROUNDED_RECT);
}

VkPageUser::~VkPageUser()
{
    delete ui;
}

void VkPageUser::setUserInfo(unsigned int userId)
{
    mId = userId;
    mPageId = QByteArray("id") + QByteArray::number(mId);

    updatePage();
}

void VkPageUser::setUserInfo(const VkUserInfoFull &userInfo)
{
    mId = userInfo.basic.id;
    mPageId = QByteArray("id") + QByteArray::number(mId);

    ui->valueUsername->setText(userInfo.basic.firstName + " " + userInfo.basic.lastName);

    //// Статус ================================================================

    ui->valueStatus->setHidden(userInfo.status.statusText.isEmpty());
    ui->valueStatus->setText(userInfo.status.statusText);

    //// Онлайн ================================================================

    if (userInfo.status.userOnline == VkUser::USER_OFFLINE)
    {
        ui->valueOnline->setText("Был в сети " + userInfo.status.lastSeen.toString());
    }
    else if (userInfo.status.userOnline == VkUser::USER_ONLINE)
    {
        ui->valueOnline->setText("online");
    }
    else if (userInfo.status.userOnline == VkUser::USER_ONLINE_MOBILE)
    {
        ui->valueOnline->setText("online");
    }
    else
        ui->valueOnline->setText("---");

    //// День рождения =========================================================

    ui->groupInfo->setHidden(userInfo.status.birthDay == 0
                             || userInfo.status.birthMonth == 0);

    if (userInfo.status.birthDay != 0 && userInfo.status.birthMonth != 0)
    {
        ui->valueBirthDate->show();
        ui->labelBirthDate->show();

        if (userInfo.status.birthYear != 0)
        {
            QDate bDate(userInfo.status.birthYear, userInfo.status.birthMonth, userInfo.status.birthDay);
            ui->valueBirthDate->setText(bDate.toString("d MMMM yyyy"));
        }
        else
        {
            ui->valueBirthDate->setText(QString::number(userInfo.status.birthDay) + " " +
                                        QDate::longMonthName(userInfo.status.birthMonth));
        }
    }

    //// Местоположения ========================================================

    ui->groupLocations->setHidden(userInfo.contacts.country.isEmpty()
                                  && userInfo.contacts.city.isEmpty()
                                  && userInfo.contacts.homeTown.isEmpty());

    //// Страна ----------------------------------------------------------------

    ui->valueCountry->setHidden(userInfo.contacts.country.isEmpty());
    ui->labelCountry->setHidden(userInfo.contacts.country.isEmpty());

    ui->valueCountry->setText(userInfo.contacts.country);

    //// Город -----------------------------------------------------------------

    ui->valueCity->setHidden(userInfo.contacts.city.isEmpty());
    ui->labelCity->setHidden(userInfo.contacts.city.isEmpty());

    ui->valueCity->setText(userInfo.contacts.city);

    //// Родной город ----------------------------------------------------------

    ui->valueHomeTown->setHidden(userInfo.contacts.homeTown.isEmpty());
    ui->labelHomeTown->setHidden(userInfo.contacts.homeTown.isEmpty());

    ui->valueHomeTown->setText(userInfo.contacts.homeTown);

    //// Телефоны ==============================================================

    ui->groupPhones->setHidden(userInfo.contacts.mobilePhone.isEmpty()
                               && userInfo.contacts.homePhone.isEmpty());

    //// Мобильный -------------------------------------------------------------

    ui->valueMobilePhone->setHidden(userInfo.contacts.mobilePhone.isEmpty());
    ui->labelMobilePhone->setHidden(userInfo.contacts.mobilePhone.isEmpty());

    ui->valueMobilePhone->setText(userInfo.contacts.mobilePhone);

    //// Другой ----------------------------------------------------------------

    ui->valueOtherPhone->setHidden(userInfo.contacts.homePhone.isEmpty());
    ui->labelOtherPhone->setHidden(userInfo.contacts.homePhone.isEmpty());

    ui->valueOtherPhone->setText(userInfo.contacts.homePhone);

    //// Счётчики ==============================================================

    ui->valueCountAlbums->setText(QString::number(userInfo.counters.albums));
    ui->valueCountPhotos->setText(QString::number(userInfo.counters.photos));
    ui->valueCountVideos->setText(QString::number(userInfo.counters.videos));
    ui->valueCountAudios->setText(QString::number(userInfo.counters.audios));
    ui->valueCountFriends->setText(QString::number(userInfo.counters.friends));

    //// Фотография ============================================================

    if (!userInfo.photo.photo_50.isEmpty())
        ui->imageProfile->setImage(userInfo.photo.photo_50);

}

void VkPageUser::userInfoReceived(QList<VkUserInfoFull> userInfoList)
{
    VkUserInfoFull currUserInfo = userInfoList.first();

    setUserInfo(currUserInfo);

    emit pageLoaded(mPageId, currUserInfo);
}

void VkPageUser::showError(const QString &errorText)
{

}

void VkPageUser::updatePage()
{
    QVkRequestUsers *requestUserInfo = new QVkRequestUsers(mToken, this);

    connect(requestUserInfo, SIGNAL(fullUserInfoReceived(QList<VkUserInfoFull>)),
            this, SLOT(userInfoReceived(QList<VkUserInfoFull>)));

    connect(requestUserInfo, SIGNAL(replyFailed(QString)),
            this, SLOT(showError(QString)));

    requestUserInfo->requestFullUserInfo(mId);
}
