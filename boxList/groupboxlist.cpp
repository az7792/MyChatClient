#include "groupboxlist.h"

GroupBoxList::GroupBoxList(QWidget *parent)
    :FriendBoxList(parent)
{}

GroupBoxList::~GroupBoxList()
{

}

void GroupBoxList::updataGroupBoxsByIds(QVector<int> ids)
{
    for(auto id:ids)
    {
        if(friendBoxMap.find(id)==friendBoxMap.end())
        {
            //添加新的群框
            FriendBox *newFriendBox = new FriendBox(UserGroupManager::getGroupByGid(id));
            addFriendBox(newFriendBox);
        }
    }
}
