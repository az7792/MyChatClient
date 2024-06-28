#include "friendboxlist.h"

FriendBoxList::FriendBoxList(QWidget *parent)
    : BoxList(parent)
{
}

FriendBoxList::~FriendBoxList()
{

}

void FriendBoxList::addFriendBox(FriendBox *friendBox)
{
    //以及存在
    if(friendBoxMap.find(friendBox->id) != friendBoxMap.end())
        return;
    //添加新的
    friendBoxMap.insert(friendBox->id,friendBox);
    connect(friendBox,&FriendBox::clicked,this,&FriendBoxList::passFriendBox);
    this->addWidget(friendBox);
}

void FriendBoxList::deleteFriendBox(int id)
{
    if(friendBoxMap.find(id) == friendBoxMap.end())
        return;
    //移除
    this->deleteWidget(friendBoxMap[id]);
}

void FriendBoxList::updataFriendBoxsByIds(QVector<int> ids)
{
    for(auto id:ids)
    {
        if(friendBoxMap.find(id)==friendBoxMap.end())
        {
            //添加新的好友框
            FriendBox *newFriendBox = new FriendBox(UserGroupManager::getUser(id));
            friendBoxMap.insert(id,newFriendBox);
            this->addWidget(newFriendBox);
        }
    }
}
