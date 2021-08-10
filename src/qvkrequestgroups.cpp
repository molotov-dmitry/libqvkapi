#include "qvkrequestgroups.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

QVkRequestGroups::QVkRequestGroups(const QByteArray& token, QObject* parent)
    : QVkRequest(token, parent, "5.131")
{

}

void QVkRequestGroups::requestGroupList(unsigned long userId, unsigned int count, unsigned int offset)
{
    disconnect(this, nullptr, this, nullptr);

    //// Список параметров =====================================================

    QParam paramList;

    //// Идентификатор пользователя --------------------------------------------

    paramList.insert("user_id", QString::number(userId));

    if (count > 0)
    {
        paramList.insert("count", QString::number(count));
    }

    paramList.insert("offset", QString::number(offset));

    //// Расширенный список полей ----------------------------------------------

    paramList.insert("extended", "1");

    //// =======================================================================

    connect(this, SIGNAL(replySuccess(QJsonDocument)),
            this, SLOT(receiveGroupList(QJsonDocument)));

    sendRequest("groups.get", paramList);
}

void QVkRequestGroups::receiveGroupList(QJsonDocument document)
{
    QList<VkGroupInfo> groupInfoList;

    QJsonObject response = document.object()["response"].toObject();

    //// Iterate trough album list =============================================

    QJsonArray items = response["items"].toArray();

    foreach (const QJsonValue &value, items)
    {
        QJsonObject object = value.toObject();
        VkGroupInfo groupInfo;

        groupInfo.id = (long)object["id"].toVariant().toULongLong();
        groupInfo.name = object["name"].toString();
        groupInfo.screenName = object["screen_name"].toString();

        groupInfo.access = (VkGroup::Access)object["is_closed"].toInt();

        if (object["deactivated"].toString() == "deleted")
        {
            groupInfo.status = VkGroup::GROUP_DELETED;
        }
        else if (object["deactivated"].toString() == "banned")
        {
            groupInfo.status = VkGroup::GROUP_BANNED;
        }
        else
        {
            groupInfo.status = VkGroup::GROUP_ACTIVE;
        }

        if (object["type"].toString() == "group")
        {
            groupInfo.type = VkGroup::GROUP_GROUP;
        }
        else if (object["type"].toString() == "page")
        {
            groupInfo.type = VkGroup::GROUP_PAGE;
        }
        else if (object["type"].toString() == "event")
        {
            groupInfo.type = VkGroup::GROUP_EVENT;
        }
        else
        {
            groupInfo.type = VkGroup::GROUP_GROUP;
        }

        groupInfo.photo_50  = object["photo_50"].toString();
        groupInfo.photo_100 = object["photo_100"].toString();
        groupInfo.photo_200 = object["photo_200"].toString();

        groupInfoList.append(groupInfo);
    }

    //// =======================================================================

    emit groupListReceived(groupInfoList);
}
