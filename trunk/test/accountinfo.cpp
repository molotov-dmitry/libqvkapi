#include "accountinfo.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

AccountInfo::AccountInfo(int id) : mId(0), mValid(false)
{
    QSqlQuery query;
    query.prepare("SELECT login, first_name, last_name, token, token_expire, image "
                  "FROM users "
                  "WHERE id = :id");

    query.bindValue(":id", id);

    query.exec();

    if (query.next())
    {
        mValid = true;
        mId = id;
        mLogin = query.value(0).toString();
        mFirstName = query.value(1).toString();
        mLastName = query.value(2).toString();
        mToken = query.value(3).toByteArray();
        mTokenExpire = QDateTime::fromTime_t(query.value(4).toUInt());

        mProfileImage = QIcon();
    }
}

bool AccountInfo::isValid() const
{
    return mValid;
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
        result = mLogin;

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

void AccountInfo::dbDelete()
{
    if (!mValid)
        return;

    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = :id");
    query.bindValue(":id", mId);

    query.exec();

    mValid = false;
}

QDateTime AccountInfo::tokenExpire() const
{
    return mTokenExpire;
}

void AccountInfo::setTokenExpire(const QDateTime &tokenExpire)
{
    mTokenExpire = tokenExpire;
}

QString AccountInfo::login() const
{
    return mLogin;
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

bool addUser(unsigned int id, const QString &login,
             const QByteArray &token, const QDateTime &tokenExpire)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM users where id = :id");
    query.bindValue(":id", id);
    query.exec();

    if (query.next())
        return false;

    query.prepare("INSERT INTO users (id, login, token, token_expire) "
                  "VALUES (:id, :login, :token, :token_expire)");

    query.bindValue(":id", id);
    query.bindValue(":login", login);
    query.bindValue(":token", token);
    query.bindValue(":token_expire", tokenExpire.toTime_t());

    if (query.exec())
    {
        return true;
    }
    else
    {
        QSqlError queryError = query.lastError();

        qDebug() << queryError.text();

        return false;
    }
}
