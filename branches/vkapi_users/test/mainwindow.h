#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "accountinfo.h"
#include "qvkuserinfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const AccountInfo &accInfo, QWidget *parent = 0);

    bool actuallyClose() const;

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    AccountInfo mAccInfo;

    bool mActuallyClose;

public slots:

    void switchSession();
    void logout();

private slots:

    void updateBasicUserInfo(QList<VkUserInfoBasic> userInfoList);

    void showError(QString errorText);
};

#endif // MAINWINDOW_H
