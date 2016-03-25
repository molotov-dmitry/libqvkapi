#include <QApplication>

#include "dialogauthorize.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DialogAuthorize authDialog;
    MainWindow w;

    if (authDialog.exec() == QDialog::Accepted)
    {
        w.show();
    }

    return a.exec();
}
