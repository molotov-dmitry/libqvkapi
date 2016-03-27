#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "accountinfo.h"

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

private slots:

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
