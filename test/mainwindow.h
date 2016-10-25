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

    void openUserPage(unsigned int pageId);
    void openUserPage(const QString &pageId);

    void openAlbumsPage(unsigned int userId);

public slots:

    void switchSession();
    void logout();

private slots:

    void updateUserInfo(QList<VkUserInfoFull> userInfoList);

    void updateUserIcon(const QImage &userProfileImage);

    void updatePageInfo(const QString &pageId, const VkUserInfoFull &info);
    void updatePageName(const QString &pageId, const QString &pageName);

    void showError(QString errorText);
    void on_buttonUpdate_clicked();
    void on_tabWidget_tabCloseRequested(int index);
    void on_tabWidget_currentChanged(int index);
    void on_buttonUser_clicked();
    void on_buttonOpenUserPageGo_clicked();
    void on_buttonOpenUserPage_toggled(bool checked);
    void on_buttonOpenLink_clicked();

    void openPage(const QString &pageUri);
};

#endif // MAINWINDOW_H
