#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "settings.h"

#include "qvkrequestusers.h"

#include "vkpagewidget.h"
#include "vkpageuser.h"

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

    connect(requestUserInfo, SIGNAL(basicUserInfoReceived(QList<VkUserInfoBasic>)),
            this, SLOT(updateBasicUserInfo(QList<VkUserInfoBasic>)));

    connect(requestUserInfo, SIGNAL(replyFailed(QString)),
            this, SLOT(showError(QString)));

    requestUserInfo->requestBasicUserInfo(accInfo.id());

    //// Create user info page =================================================

    VkPageUser *page = new VkPageUser(0);
    page->setToken(accInfo.token());
    page->setUserInfo(accInfo.id());

    mPages.append(page);
    mCurrentPage = page;

    ui->tabWidget->addTab(page, QIcon::fromTheme("folder-home"), "Моя Страница");
}

bool MainWindow::actuallyClose() const
{
    return mActuallyClose;
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::updateBasicUserInfo(QList<VkUserInfoBasic> userInfoList)
{
    VkUserInfoBasic currUserInfo = userInfoList.first();

    mAccInfo.setFirstName(currUserInfo.firstName);
    mAccInfo.setLastName(currUserInfo.lastName);

    ui->buttonUser->setText(mAccInfo.firstName());
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
    for (int i = 0; i < mPages.count(); ++i)
    {
        VkPageWidget *page = mPages.at(i);

        if (page->getPageId() == QByteArray("id") + QByteArray::number(mAccInfo.id()))
        {
            ui->tabWidget->setCurrentIndex(i);
            return;
        }
    }

    VkPageUser *page = new VkPageUser(0);
    page->setToken(mAccInfo.token());
    page->setUserInfo(mAccInfo.id());

    mPages.append(page);
    mCurrentPage = page;

    int newTabIndex = ui->tabWidget->addTab(page, QIcon::fromTheme("folder-home"), "Моя Страница");

    if (newTabIndex >= 0)
        ui->tabWidget->setCurrentIndex(newTabIndex);
}
