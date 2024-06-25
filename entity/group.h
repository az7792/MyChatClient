#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QPixmap>

class Group : public QObject
{
    Q_OBJECT

public:
    explicit Group(QObject *parent = nullptr);
    Group(int groupid, QString groupname, int ownerid, QObject *parent = nullptr);

    int getGroupid();
    QString getGroupname();
    int getOwnerid();
    void setGroupid(int groupid);
    void setGroupname(QString groupname);
    void setOwnerid(int ownerid);
    QPixmap getAvatar();

    static Group toGroup(QJsonObject jsonObject);

private:
    int groupid = -1;
    int ownerid = -1;
    QString groupname;
};

#endif // GROUP_H
