#include "messageboxlist.h"
#include <QLabel>

MessageBoxList::MessageBoxList(QWidget *parent)
    : BoxList(parent)
{
}

MessageBoxList::~MessageBoxList()
{

}

void MessageBoxList::addMessageBox(MessageBox *messageBox)
{
    //以及存在
    if(messageBoxMap.find(qMakePair(messageBox->id,messageBox->chatType)) != messageBoxMap.end())
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
                MessageBox *newMessageBox = new MessageBox(this);
                User tmp = UserGroupManager::getUser(message.fromUserUid);
                newMessageBox->setAvatar(tmp.getAvatar());
                newMessageBox->setName(tmp.getUsername());
                newMessageBox->setNumUnread(0);
                newMessageBox->id = message.fromUserUid;
                newMessageBox->chatType = message.receiverType;
                newMessageBox->uid = this->UID;
                newMessageBox->addMessage(message);
                addMessageBox(newMessageBox);
            }else{
                (*it)->addMessage(message);
            }
        }else{//group
            auto it = messageBoxMap.find(qMakePair(message.toReceiver,message.receiverType));
            if(it == messageBoxMap.end()){
                //新建一个
                MessageBox *newMessageBox = new MessageBox(this);
                Group tmpGroup = UserGroupManager::getGroupByGid(message.toReceiver);
                newMessageBox->setAvatar(tmpGroup.getAvatar());
                newMessageBox->setName(tmpGroup.getGroupname());
                newMessageBox->setNumUnread(0);
                newMessageBox->id = message.toReceiver;
                newMessageBox->chatType = message.receiverType;
                newMessageBox->uid = this->UID;
                newMessageBox->addMessage(message);
                addMessageBox(newMessageBox);
            }else{
                (*it)->addMessage(message);
            }
        }
    }
}
