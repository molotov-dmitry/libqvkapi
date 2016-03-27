#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "qvkauth.h"

MainWindow::MainWindow(const AccountInfo &accInfo, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

bool MainWindow::actuallyClose() const
{
    return false;
}

MainWindow::~MainWindow()
{
    delete ui;
}
