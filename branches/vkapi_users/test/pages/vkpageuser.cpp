#include "vkpageuser.h"
#include "ui_vkpageuser.h"

#include <QPalette>
#include <QDateTime>

#include <qvkrequestusers.h>

#include "resicons.h"
#include "metadata.h"

VkPageUser::VkPageUser(QWidget *parent) :
    VkPageWidget(parent),
    ui(new Ui::VkPageUser)
{
    ui->setupUi(this);
    setPageContent(ui->widgetStateLoaded, ui->mainLayout);

    setIcon(ui->buttonAlbums, "cat_albums.svg");
    setIcon(ui->buttonPhotos, "cat_photos.svg");
    setIcon(ui->buttonVideos, "cat_videos.svg");
    setIcon(ui->buttonAudios, "cat_audios.svg");
    setIcon(ui->buttonFriends, "cat_friends.svg");

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
    mPageId = QByteArray("id") + QByteArray::number(userId);
    mPageName.clear();

    updatePage();
}

void VkPageUser::setUserInfo(const QString &userName)
{
    bool isNumber;
    userName.toUInt(&isNumber);

    if (isNumber)
    {
        mPageId = QByteArray("id") + userName.toLocal8Bit();
        mPageName.clear();
    }
    else
    {
        mPageId.clear();
        mPageName = userName.toLocal8Bit();
    }

    updatePage();
}

void VkPageUser::setUserInfo(const VkUserInfoFull &userInfo)
{
    mPageId = QByteArray("id") + QByteArray::number(userInfo.basic.id);

    setPageStatus(PAGE_LOADED);

    if (!userInfo.status.screenName.isEmpty() && userInfo.status.screenName != mPageId)
        mPageName = userInfo.status.screenName.toLocal8Bit();
    else
        mPageName.clear();

    ui->valueUsername->setText(userInfo.basic.firstName + " " + userInfo.basic.lastName);

    //// Статус ================================================================

    ui->valueStatus->setHidden(userInfo.status.statusText.isEmpty());
    ui->valueStatus->setText(userInfo.status.statusText);

    //// Онлайн ================================================================

    if (userInfo.status.userOnline == VkUser::USER_OFFLINE)
    {
        QString wasStr;

        if (userInfo.status.userSex == VkUser::USER_FEMALE)
            wasStr = "Была";
        else
            wasStr = "Был";

        qint64 secondsDiff = userInfo.status.lastSeen.secsTo(QDateTime::currentDateTime());

        if (secondsDiff < 60 * 15)
        {
            ui->valueOnline->setIcon(QIcon::fromTheme("user-away"));
            setIcon(ui->valueOnline, "user-away.svg");

            ui->valueOnline->setText(wasStr + " в сети "
                                     + Metadata::timeDiffStr(userInfo.status.lastSeen));

        }
        else if (secondsDiff < 60 * 60 * 3)
        {
            ui->valueOnline->setIcon(QIcon::fromTheme("user-offline"));
            setIcon(ui->valueOnline, "user-offline.svg");

            ui->valueOnline->setText(wasStr + " в сети "
                                     + Metadata::timeDiffStr(userInfo.status.lastSeen));
        }
        else
        {
            ui->valueOnline->setIcon(QIcon::fromTheme("user-offline"));
            setIcon(ui->valueOnline, "user-offline.svg");

            ui->valueOnline->setText(wasStr + " в сети "
                                     + Metadata::dateDiffStr(userInfo.status.lastSeen));
        }
    }
    else if (userInfo.status.userOnline == VkUser::USER_ONLINE)
    {
        ui->valueOnline->setIcon(QIcon::fromTheme("user-available"));
        setIcon(ui->valueOnline, "user-available.svg");

        ui->valueOnline->setText("В сети");
    }
    else if (userInfo.status.userOnline == VkUser::USER_ONLINE_MOBILE)
    {
        ui->valueOnline->setIcon(QIcon::fromTheme("user-available"));
        setIcon(ui->valueOnline, "user-available.svg");

        ui->valueOnline->setText("В сети");
    }
    else
    {
        ui->valueOnline->setIcon(QIcon::fromTheme("user-busy"));
        setIcon(ui->valueOnline, "user-busy.svg");

        ui->valueOnline->setText("---");
    }

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
            ui->valueBirthDate->setText(bDate.toString("d MMMM yyyy") + " г.");
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

void VkPageUser::updatePage()
{
    QVkRequestUsers *requestUserInfo = new QVkRequestUsers(mToken, this);

    connect(requestUserInfo, SIGNAL(fullUserInfoReceived(QList<VkUserInfoFull>)),
            this, SLOT(userInfoReceived(QList<VkUserInfoFull>)));

    connect(requestUserInfo, SIGNAL(replyFailed(QString)),
            this, SLOT(setError(QString)));

    QStringList userIds;

    if (!mPageId.isEmpty())
        userIds << mPageId;
    else
        userIds << mPageName;

    requestUserInfo->requestFullUserInfo(userIds);
}
