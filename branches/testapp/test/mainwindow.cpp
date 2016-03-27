#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settings.h"

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
    mActuallyClose = false;
    close();
}
