#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnLogin_clicked();

    void authSuccess(const QByteArray &token,
                     const QDateTime &tokenExpire,
                     int userId);

    void authFailed(const QString &error);

    void authProgress(int progress);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
