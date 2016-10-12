#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <QPainter>

#include "settings.h"

#include "qvkrequestusers.h"

#include "vkpagewidget.h"
#include "vkpageuser.h"

#include "imagecache.h"

#include "resicons.h"

MainWindow::MainWindow(const AccountInfo &accInfo, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mAccInfo(accInfo),
    mActuallyClose(true)
{
    ui->setupUi(this);

    if (windowIcon().isNull())
        setWindowIcon(QIcon(":/icons/icon.svg"));

    setIcon(ui->buttonLogout, "user-logout.svg");
    setIcon(ui->buttonSwitchUser, "user-switch.svg");
    setIcon(ui->buttonUpdate, "refresh.svg");

    ui->buttonUser->setText(accInfo.visibleName());

    Settings::setSetting("current_id", QString::number(accInfo.id()));

    //// Request user info =====================================================

    QVkRequestUsers *requestUserInfo = new QVkRequestUsers(accInfo.token(), this);

    connect(requestUserInfo, SIGNAL(fullUserInfoReceived(QList<VkUserInfoFull>)),
            this, SLOT(updateUserInfo(QList<VkUserInfoFull>)));

    connect(requestUserInfo, SIGNAL(replyFailed(QString)),
            this, SLOT(showError(QString)));

    requestUserInfo->requestFullUserInfo(accInfo.id());

    //// Open page edit ========================================================

    ui->editUserName->hide();
    ui->buttonOpenUserPageGo->hide();

}

bool MainWindow::actuallyClose() const
{
    return mActuallyClose;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openUserPage(unsigned int pageId)
{
    openUserPage(QString::number(pageId));
}

void MainWindow::openUserPage(const QString &userId)
{
    for (int i = 0; i < mPages.count(); ++i)
    {
        VkPageWidget *page = mPages.at(i);

        if (page->isThisPage(userId))
        {
            ui->tabWidget->setCurrentIndex(i);
            return;
        }
    }

    VkPageUser *page = new VkPageUser(0);
    page->setToken(mAccInfo.token());
    page->setUserInfo(userId);

    connect(page, SIGNAL(pageLoaded(QString,VkUserInfoFull)), this, SLOT(updatePageInfo(QString,VkUserInfoFull)));

    mPages.append(page);
    mCurrentPage = page;

    int newTabIndex = ui->tabWidget->addTab(page, QIcon::fromTheme("user-identity"), userId);

    if (newTabIndex >= 0)
        ui->tabWidget->setCurrentIndex(newTabIndex);
}

void MainWindow::switchSession()
{
    mActuallyClose = false;
    close();
}

void MainWindow::logout()
{
    QMessageBox::StandardButton result;

    result = QMessageBox::question(this,
                                   trUtf8("Завершение сессии"),
                                   trUtf8("Вы действительно хотите завершить сессию?"));

    if (result == QMessageBox::Yes)
    {
        mAccInfo.dbDelete();
        mActuallyClose = false;
        close();
    }
}

void MainWindow::updateUserInfo(QList<VkUserInfoFull> userInfoList)
{
    VkUserInfoFull currUserInfo = userInfoList.first();

    mAccInfo.setFirstName(currUserInfo.basic.firstName);
    mAccInfo.setLastName(currUserInfo.basic.lastName);

    mAccInfo.setProfileImageName(currUserInfo.photo.photo_50);

    ui->buttonUser->setEnabled(true);
    ui->buttonUser->setText(mAccInfo.firstName());

    //// Create user info page =================================================

    VkPageUser *page = new VkPageUser(0);

    page->setToken(mAccInfo.token());
    page->setUserInfo(currUserInfo);

    mPages.append(page);
    mCurrentPage = page;

    ui->tabWidget->addTab(page, QIcon::fromTheme("folder-home"), "Моя Страница");

    //// Request user profile image ============================================

    ImageCache *imageCache = new ImageCache(this);

    connect(imageCache, SIGNAL(imageLoaded(QImage)), this, SLOT(updateUserIcon(QImage)));

    imageCache->loadImage(currUserInfo.photo.photo_50);

}

void MainWindow::updateUserIcon(const QImage &userProfileImage)
{
    QPixmap userPixmap(ui->buttonUser->iconSize());
    userPixmap.fill(Qt::transparent);

    QPainter p(&userPixmap);

    p.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setTextureImage(userProfileImage.scaled(p.window().size()));

    p.setBrush(brush);
    p.setPen(Qt::NoPen);

    p.drawEllipse(p.window());

    p.end();

    ui->buttonUser->setIcon(QIcon(userPixmap));
}

void MainWindow::updatePageInfo(const QString &pageId, const VkUserInfoFull &info)
{
    for (int i = 0; i < mPages.count(); ++i)
    {
        VkPageWidget *page = mPages.at(i);

        if (page->getPageId() == pageId)
        {
            ui->tabWidget->setTabText(i, info.basic.firstName + " " + info.basic.lastName);
        }
    }
}

void MainWindow::showError(QString errorText)
{
    QMessageBox::critical(this, "Error", errorText);
}

void MainWindow::on_buttonUpdate_clicked()
{
    if (mCurrentPage)
        mCurrentPage->updatePage();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (mPages.count() > index)
    {
        mPages.removeAt(index);
        ui->tabWidget->removeTab(index);
    }

    if (mPages.isEmpty())
    {
        mCurrentPage = 0;
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index < 0 || index >= mPages.count())
        mCurrentPage = 0;
    else
        mCurrentPage = mPages.at(index);
}

void MainWindow::on_buttonUser_clicked()
{
    openUserPage(mAccInfo.id());
}

void MainWindow::on_buttonOpenUserPage_clicked()
{
    ui->buttonOpenUserPageGo->show();

    ui->editUserName->show();
    ui->editUserName->setFocus();
}

void MainWindow::on_buttonOpenUserPageGo_clicked()
{
    QString userId = ui->editUserName->text();

    ui->buttonOpenUserPageGo->hide();

    ui->editUserName->clear();
    ui->editUserName->hide();

    openUserPage(userId);
}
