#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "qvkauth.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnLogin_clicked()
{
    QVkAuth *vkAuth = new QVkAuth(this);

    connect(vkAuth, SIGNAL(authSuccess(QByteArray,QDateTime,int)),
            this, SLOT(authSuccess(QByteArray,QDateTime,int)));

    connect(vkAuth, SIGNAL(authFailed(QString)),
            this, SLOT(authFailed(QString)));

    connect(vkAuth, SIGNAL(authProgress(int)),
            this, SLOT(authProgress(int)));

    vkAuth->setAppId("5172032");
    vkAuth->authenticate(ui->editLogin->text(), ui->editPassword->text());
}

void MainWindow::authSuccess(const QByteArray &token, const QDateTime &tokenExpire, int userId)
{
    QMessageBox::information(this,
                             QString::fromUtf8("Аутентификация"),
                             QString::fromUtf8("Успешная аутентификация"));
}

void MainWindow::authFailed(const QString &error)
{
    QMessageBox::critical(this, QString::fromUtf8("Ошибка аутентификации"), error);
}

void MainWindow::authProgress(int progress)
{
    ui->authProgressBar->setValue(progress);
}
