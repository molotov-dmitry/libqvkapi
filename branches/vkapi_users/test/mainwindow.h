#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "accountinfo.h"
#include "qvkuserinfo.h"

#include "vkpagewidget.h"

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

    QList<VkPageWidget*> mPages;
    VkPageWidget* mCurrentPage;

public slots:

    void switchSession();
    void logout();

private slots:

    void updateBasicUserInfo(QList<VkUserInfoBasic> userInfoList);

    void showError(QString errorText);
    void on_buttonUpdate_clicked();
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_currentChanged(int index);
    void on_buttonUser_clicked();
};

#endif // MAINWINDOW_H
