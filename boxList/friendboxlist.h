#ifndef FRIENDBOXLIST_H
#define FRIENDBOXLIST_H

#include "boxList/boxlist.h"
#include "smallWidget/friendbox.h"
#include "manager/usergroupmanager.h"
class FriendBoxList: public BoxList
{
    Q_OBJECT
public:
    explicit FriendBoxList(QWidget *parent = nullptr);
    ~FriendBoxList();
    void addFriendBox(FriendBox *friendBox);
    void deleteFriendBox(int id);
    void updataFriendBoxsByIds(QVector<int>ids);
private:
    QMap<int,FriendBox*> friendBoxMap;

signals:
    void passFriendBox(FriendBox *friendBox);
};

#endif // FRIENDBOXLIST_H
