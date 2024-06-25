#include "group.h"

Group::Group(QObject *parent)
    : QObject(parent), groupid(-1), ownerid(-1)
{}

Group::Group(int groupid, QString groupname, int ownerid, QObject *parent)
    : QObject(parent), groupid(groupid), groupname(groupname), ownerid(ownerid)
{}

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

void Group::setGroupname(QString groupname) {
    this->groupname = groupname;
}

void Group::setOwnerid(int ownerid) {
    this->ownerid = ownerid;
}

Group* Group::toGroup(QJsonObject jsonObject)
{
    if(jsonObject.isEmpty())
        return new Group();  // 返回新创建的Group对象的指针，使用默认的parent为nullptr

    return new Group(jsonObject["groupid"].toInt(), jsonObject["groupname"].toString(), jsonObject["ownerid"].toInt());
    // 返回新创建的Group对象的指针
}

QPixmap Group::getAvatar()
{
    return QPixmap(":/img/resources/defaultAvatar.jpg");
}
