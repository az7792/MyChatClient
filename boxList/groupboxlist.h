#ifndef GROUPBOXLIST_H
#define GROUPBOXLIST_H
#include "boxList/friendboxlist.h"
class GroupBoxList: public FriendBoxList
{
    Q_OBJECT
public:
    explicit GroupBoxList(QWidget *parent = nullptr);
    ~GroupBoxList();
    void updataGroupBoxsByIds(QVector<int>ids);
};

#endif // GROUPBOXLIST_H
