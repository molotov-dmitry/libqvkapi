#include <QApplication>

#include <QSqlDatabase>

#include "dialogauthorize.h"
#include "mainwindow.h"
#include "settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db/vk.db");
    if (!db.open())
        return 1;

    while (1)
    {
        unsigned int currentId = Settings::getSetting("current_id", "0").toUInt();

        AccountInfo accInfo(currentId);

        if (!accInfo.isValid())
        {
            DialogAuthorize d;

            if (d.exec() != QDialog::Accepted)
                break;

            accInfo = d.currentAccountInfo();
        }

        MainWindow w(accInfo);
        w.showMaximized();

        int result = a.exec();

        if (result || w.actuallyClose())
            return result;
    }

    return 0;
}
