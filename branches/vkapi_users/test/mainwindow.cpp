#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "settings.h"

#include "qvkrequestusers.h"

MainWindow::MainWindow(const AccountInfo &accInfo, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mAccInfo(accInfo),
    mActuallyClose(true)
{
    ui->setupUi(this);

    if (windowIcon().isNull())
        setWindowIcon(QIcon(":/icons/icon.svg"));

    if (ui->buttonLogout->icon().isNull())
        ui->buttonLogout->setIcon(QIcon(":/icons/user-logout.svg"));

    if (ui->buttonSwitchUser->icon().isNull())
        ui->buttonSwitchUser->setIcon(QIcon(":/icons/user-switch.svg"));

    ui->labelName->setText(accInfo.visibleName());

    Settings::setSetting("current_id", QString::number(accInfo.id()));

    QVkRequestUsers *requestUserInfo = new QVkRequestUsers(accInfo.token(), this);

    connect(requestUserInfo, SIGNAL(basicUserInfoReceived(QList<VkUserInfoBasic>)),
            this, SLOT(updateBasicUserInfo(QList<VkUserInfoBasic>)));

    connect(requestUserInfo, SIGNAL(replyFailed(QString)),
            this, SLOT(showError(QString)));

    requestUserInfo->requestBasicUserInfo(accInfo.id());
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
    mAccInfo.dbDelete();
    mActuallyClose = false;
    close();
}

void MainWindow::updateBasicUserInfo(QList<VkUserInfoBasic> userInfoList)
{
    VkUserInfoBasic currUserInfo = userInfoList.first();

    mAccInfo.setFirstName(currUserInfo.firstName);
    mAccInfo.setLastName(currUserInfo.lastName);

    ui->labelName->setText(mAccInfo.visibleName());
}

void MainWindow::showError(QString errorText)
{
    QMessageBox::critical(this, "Error", errorText);
}
