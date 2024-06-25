#include "group.h"

Group::Group() {}

Group::Group(int groupid, QString groupname, int ownerid)
    : groupid(groupid), ownerid(ownerid),groupname(groupname)
{

}

int Group::getGroupid()
{
    return this->groupid;
}

QString Group::getGroupname()
{
    return this->groupname;
}

int Group::getOwnerid()
{
    return this->ownerid;
}

void Group::setGroupid(int groupid) {
    this->groupid = groupid;
}


void Group::setUsername(QString groupname) {
    this->groupname = groupname;
}


void Group::setOwnerid(int ownerid) {
    this->ownerid = ownerid;
}

Group Group::toGroup(QJsonObject jsonObject)
{
    //az77927792
    // 解析响应
    if(jsonObject.isEmpty())
        return Group();
    // QString avatarString = jsonObject["avatar"].toString();
    // // 将Base64字符串转换为QPixmap
    // QByteArray byteArray = QByteArray::fromBase64(avatarString.toUtf8());
    // QPixmap avatar;
    // if (!byteArray.isEmpty()) {
    //     avatar.loadFromData(byteArray);
    // }
    Group group(jsonObject["groupid"].toInt(),jsonObject["groupname"].toString(),jsonObject["ownerid"].toInt());
    return group;
}
QPixmap Group::getAvatar()
{
    return QPixmap(":/img/resources/defaultAvatar.jpg");
}
