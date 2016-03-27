#include <QApplication>

#include <QSqlDatabase>
#include <QSqlQuery>

#include "dialogauthorize.h"
#include "mainwindow.h"
#include "settings.h"

#include <sys/stat.h>

const int CURRENT_DB_VERSION = 1;

bool migrateDb(QSqlDatabase &db,
               int versionFrom, int versionTo = CURRENT_DB_VERSION)
{
    for (int from = versionFrom; from < versionTo; from++)
    {
        int to = from + 1;

        db.transaction();

        switch (from)
        {
        //// Create database ---------------------------------------------------
        case 0:
        {
            QSqlQuery query;

            bool res;
            res = query.exec("CREATE TABLE settings ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                             "name TEXT UNIQUE ON CONFLICT REPLACE NOT NULL,"
                             "value TEXT);"
                             );

            res &= query.exec("CREATE TABLE users ("
                              "id INTEGER PRIMARY KEY NOT NULL,"
                              "login TEXT NOT NULL,"
                              "first_name TEXT,"
                              "last_name TEXT,"
                              "token TEXT NOT NULL,"
                              "token_expire INTEGER NOT NULL,"
                              "image BLOB);");

            if (!res)
            {
                db.rollback();
                return false;
            }

            break;
        }

            //// Do nothing ----------------------------------------------------

        default:
        {
            break;
        }
        }

        if (!Settings::setSetting("db_version", QString::number(to)))
        {
            db.rollback();
            return false;
        }

        db.commit();
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //// Open database ---------------------------------------------------------

    mkdir("db", 0744);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db/vk.db");
    if (!db.open())
        return 1;

    //// Check database verison ------------------------------------------------

    int dbVersion = Settings::getSetting("db_version", "0").toInt();

    if (dbVersion < CURRENT_DB_VERSION)
        if (!migrateDb(db, dbVersion))
            return 2;

    //// Start -----------------------------------------------------------------

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

        Settings::setSetting("current_id", "0");
    }

    return 0;
}
