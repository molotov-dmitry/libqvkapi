#include "qvkrequestfriends.h"

QVkRequestFriends::QVkRequestFriends(const QByteArray& token, QObject* parent)
{

}

void QVkRequestFriends::requestFriendList(unsigned long userId, unsigned int count, unsigned int offset)
{
    //bdate,photo_50, photo_100, photo_200_orig,online,last_seen,status,verified
}

void QVkRequestFriends::receiveFriendList(QJsonDocument document)
{

}
