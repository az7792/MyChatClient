#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QPixmap>

class Group
{
public:
    Group();
    Group(int groupid,QString groupname,int ownerid,QPixmap Avatar);

    int getGroupid();
    int getOwnerid();
    QString getGroupname();
    void setGroupid(int groupid);
    void setUsername(QString groupname);
    void setOwnerid(int ownerid);
    QPixmap getAvatar();


    static Group toGroup(QJsonObject jsonObject);


private:
    int groupid=-1;
    int ownerid = -1;
    QString groupname;
    QPixmap Avatar;
};

#endif // GROUP_H
