#include "accountinfo.h"

#include <QSqlQuery>
#include <QVariant>

AccountInfo::AccountInfo(int id) : mId(0)
{
    QSqlQuery query;
    query.prepare("SELECT first_name, last_name, token, image "
                  "FROM users "
                  "WHERE id = :id");

    query.bindValue(":id", id);

    query.exec();

    if (query.next())
    {
        mId = id;
        mFirstName = query.value(0).toString();
        mLastName = query.value(1).toString();
        mToken = query.value(2).toByteArray();

        mProfileImage = QIcon();
    }
}

unsigned int AccountInfo::id() const
{
    return mId;
}

QString AccountInfo::firstName() const
{
    return mFirstName;
}

QString AccountInfo::lastName() const
{
    return mLastName;
}

QString AccountInfo::visibleName() const
{
    QString result = QString(mFirstName + " " + mLastName).trimmed();

    if (result.isEmpty())
        result = QString("id") + QString::number(mId);

    return result;
}

QByteArray AccountInfo::token() const
{
    return mToken;
}

QIcon AccountInfo::profileImage() const
{
    return mProfileImage;
}

AccountList getAccountList()
{
    AccountList accList;

    QSqlQuery query;
    query.exec("SELECT id FROM users");

    while (query.next())
    {
        int id = query.value(0).toInt();

        AccountInfo accInfo(id);

        accList.append(accInfo);
    }

    return accList;
}
