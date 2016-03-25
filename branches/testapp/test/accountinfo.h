#ifndef ACCOUNTINFO_H
#define ACCOUNTINFO_H

#include <QObject>
#include <QList>

#include <QIcon>

class AccountInfo
{
public:
    explicit AccountInfo(int id = 0);

    unsigned int id() const;

    QString firstName() const;
    QString lastName() const;

    QString visibleName() const;

    QByteArray token() const;

    QIcon profileImage() const;

private:

    unsigned int mId;

    QByteArray  mToken;

    QString mFirstName;
    QString mLastName;

    QIcon   mProfileImage;

};

Q_DECLARE_METATYPE(AccountInfo)

typedef QList<AccountInfo> AccountList;

AccountList getAccountList();

#endif // ACCOUNTINFO_H
