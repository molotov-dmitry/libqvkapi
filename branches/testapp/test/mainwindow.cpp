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
