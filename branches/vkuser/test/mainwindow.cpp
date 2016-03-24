#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include "qvkapi.h"
#include "qvkapiusers.h"

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
    QVkApi *vkApi = new QVkApi(this);

    connect(vkApi, SIGNAL(authorizationSuccess(QByteArray,QDateTime,int)),
            this, SLOT(authSuccess(QByteArray,QDateTime,int)));

    connect(vkApi, SIGNAL(authorizationFailed(QString)),
            this, SLOT(authFailed(QString)));

    connect(vkApi, SIGNAL(authorizationProgress(int)),
            this, SLOT(authProgress(int)));

    vkApi->setAppId("5172032");
    vkApi->authorize(ui->editLogin->text(), ui->editPassword->text());
}

void MainWindow::authSuccess(const QByteArray &token, const QDateTime &tokenExpire, int userId)
{
    QMessageBox::information(this,
                             QString::fromUtf8("Авторизация"),
                             QString::fromUtf8("Успешная авторизация"));

    QVkApiUsers *vkApiUsers = new QVkApiUsers(this);

    QList<unsigned int> userIdList;

    userIdList.append(1);
    userIdList.append(345345345);

    vkApiUsers->requestUserInfo(token, userIdList);
}

void MainWindow::authFailed(const QString &error)
{
    QMessageBox::critical(this, QString::fromUtf8("Ошибка авторизации"), error);
}

void MainWindow::authProgress(int progress)
{
    ui->authProgressBar->setValue(progress);
}
