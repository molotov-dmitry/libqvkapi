/*!
  \file
  \brief Файл с описанием класса запросов информации о пользователях
*/
#ifndef QVKREQUESTUSERS_H
#define QVKREQUESTUSERS_H

#include "qvkuserinfo.h"
#include "qvkrequest.h"

class QVkRequestUsers : public QVkRequest
{
    Q_OBJECT

public:
    explicit QVkRequestUsers(const QByteArray &token = QByteArray(),
                             QObject *parent = 0);

    void requestBasicUserInfo(unsigned long userId);

    void requestBasicUserInfo(QStringList userIds);

private slots:

    void receiveBasicUserInfo(QJsonDocument document);

signals:

    void basicUserInfoReceived(QList<VkUserInfoBasic> userInfoList);
};

#endif // QVKREQUESTUSERS_H
