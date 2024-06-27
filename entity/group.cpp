#include "group.h"

Group::Group() {}

Group::Group(int groupid, QString groupname, int ownerid,QPixmap Avatar)
    : groupid(groupid), ownerid(ownerid),groupname(groupname),Avatar(Avatar)
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
    if(jsonObject.isEmpty())
        return Group();
    Group group(jsonObject["groupid"].toInt(),jsonObject["groupname"].toString(),jsonObject["ownerid"].toInt(),jsonObject["avatar"].toString());
    return group;
}
QPixmap Group::getAvatar()
{
    return Avatar;
}
