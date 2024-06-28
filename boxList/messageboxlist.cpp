#include "messageboxlist.h"
#include <QLabel>

MessageBoxList::MessageBoxList(QWidget *parent)
    : BoxList(parent)
{
}

MessageBoxList::~MessageBoxList()
{

}

bool MessageBoxList::hasMessageBox(QPair<int, QString> index)
{
    if(messageBoxMap.find(index) != messageBoxMap.end())
        return true;
    else
        return false;
}

MessageBox *MessageBoxList::getMessageBoxByUser(User tmpUser)
{
    MessageBox * newMessageBox = new MessageBox(this);
    newMessageBox->setName(tmpUser.getUsername());
    newMessageBox->setId(tmpUser.getUID());
    newMessageBox->setNumUnread(0);
    newMessageBox->setTime(QDateTime::currentDateTime());
    newMessageBox->setAvatar(tmpUser.getAvatar());
    newMessageBox->setNewMessage("");
    newMessageBox->setChatType("user");
    newMessageBox->uid = this->UID;
    return newMessageBox;
}

MessageBox *MessageBoxList::getMessageBoxByGroup(Group tmpGroup)
{
    MessageBox * newMessageBox = new MessageBox(this);
    newMessageBox->setName(tmpGroup.getGroupname());
    newMessageBox->setId(tmpGroup.getGroupid());
    newMessageBox->setNumUnread(0);
    newMessageBox->setTime(QDateTime::currentDateTime());
    newMessageBox->setAvatar(tmpGroup.getAvatar());
    newMessageBox->setNewMessage("");
    newMessageBox->setChatType("group");
    newMessageBox->uid = this->UID;
    return newMessageBox;
}

void MessageBoxList::addMessageBox(MessageBox *messageBox)
{
    //已经存在
    if(hasMessageBox(qMakePair(messageBox->id,messageBox->chatType)))
        return;
    //添加新的
    messageBoxMap.insert(qMakePair(messageBox->id,messageBox->chatType),messageBox);
    connect(messageBox,&MessageBox::clicked,this,&MessageBoxList::passMessageBox);
    this->addWidget(messageBox);
}

void MessageBoxList::deleteMessageBox(QPair<int,QString> index)
{
    //不存在
    if(messageBoxMap.find(index) == messageBoxMap.end())
        return;
    //移除
    this->deleteWidget(messageBoxMap[index]);
}

void MessageBoxList::updataMessageBox(Message message)
{
    if(message.fromUserUid == this->UID){//我发给别人
        auto it = messageBoxMap.find(qMakePair(message.toReceiver,message.receiverType));
        if(it == messageBoxMap.end()){
            //新建一个
            // MessageBox *newMessageBox = new MessageBox();
            // if(message.receiverType=="user")
            //     newMessageBox->avatar = UserGroupManager::getUser(message.toReceiver).getAvatar();
            // else
            //     newMessageBox->avatar = UserGroupManager::getUser(message.toReceiver).getAvatar();

            // newMessageBox->setNumUnread(0);
            // newMessageBox->id = message.toReceiver;
            // newMessageBox->uid = this->UID;
            // newMessageBox->addMessage(message);

            // addMessageBox(newMessageBox);
        }else{
            (*it)->addMessage(message);
        }
    }else{//我接收别人的
        if(message.receiverType=="user"){
            auto it = messageBoxMap.find(qMakePair(message.fromUserUid,message.receiverType));
            if(it == messageBoxMap.end()){
                //新建一个                
                User tmp = UserGroupManager::getUser(message.fromUserUid);
                MessageBox *newMessageBox = getMessageBoxByUser(tmp);
                newMessageBox->addMessage(message);
                addMessageBox(newMessageBox);
            }else{
                (*it)->addMessage(message);
            }
        }else{//group
            auto it = messageBoxMap.find(qMakePair(message.toReceiver,message.receiverType));
            if(it == messageBoxMap.end()){
                //新建一个
                Group tmpGroup = UserGroupManager::getGroupByGid(message.toReceiver);
                MessageBox *newMessageBox = getMessageBoxByGroup(tmpGroup);
                newMessageBox->addMessage(message);
                addMessageBox(newMessageBox);
            }else{
                (*it)->addMessage(message);
            }
        }
    }
}
