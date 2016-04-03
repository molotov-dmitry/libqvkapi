#include "settings.h"

#include <QSqlQuery>
#include <QVariant>

QString Settings::getSetting(const QString &name, const QString &defaultValue)
{
    QSqlQuery query;
    query.exec(QString("SELECT value FROM settings WHERE name = '%1'").arg(name));

    if (query.next())
        return query.value(0).toString();
    else
        return defaultValue;
}

bool Settings::setSetting(const QString &name, const QString &value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO settings (name, value) VALUES (:name, :value)");

    query.bindValue(":name", name);
    query.bindValue(":value", value);

    return query.exec();
}
