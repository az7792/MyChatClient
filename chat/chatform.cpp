#include "chatform.h"
#include "ui_chatform.h"

#include <QTimer>

ChatForm::ChatForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatForm)
{
    ui->setupUi(this);
    //删除ui中自带的前两个页面
    for (int i = 0; i < ui->stackedWidget->count(); ++i)
    {
        QWidget *widget = ui->stackedWidget->widget(0);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
    connect(&chatWebsocket,&ChatWebSocket::textMessageReceived,this,&ChatForm::onTextMessageReceived);//websocket收到消息转到槽函数处理
}

ChatForm::~ChatForm()
{
    delete ui;
}

void ChatForm::initRecvUsers(int toId, QString chatType)
{
    //加载成员
    this->chatType = chatType;
    this->toId=toId;
    recvUsers.clear();
    if(chatType == "user")
    {
        User recvUser = UserGroupManager::getUser(toId);
        recvUsers.insert(recvUser.getUID(),recvUser);        
    }
    else//group
    {
        //加载群成员
        QVector<User>Users = UserGroupManager::getGroupMembers(toId);
        for(auto v:Users){
            recvUsers.insert(v.getUID(),v);
        }
    }
}

void ChatForm::on_SendPushButton_clicked()//发送
{
    if(ui->plainTextEdit->toPlainText()=="" || toId==-1 || sendUser.getUID() == -1)//消息为空或者无接受者
        return;
    QString text = ui->plainTextEdit->toPlainText();
    Message message(sendUser.getUID(),toId,chatType,text,"text");
    chatWebsocket.sendMessage(message);
    ui->plainTextEdit->setPlainText("");
    //显示聊天
    addSendBox(text);
    //发送存储聊天信号
    message.sentTime = QDateTime::currentDateTime();
    message.isRead = 1;
    emit saveToMessageBox(message);
}

void ChatForm::onTextMessageReceived(const QString &messageString)
{
    Message message = Message::toMessage(messageString);
    //判断是否在当前窗口展示消息
    if(toId == -1){
        emit saveToMessageBox(message);
        return;
    }
    if(message.receiverType != chatType){
        emit saveToMessageBox(message);
        return;
    }
    if(message.receiverType == "user" && message.fromUserUid != toId){
        emit saveToMessageBox(message);
        return;
    }
    if(message.receiverType == "group" && message.toReceiver != toId){
        emit saveToMessageBox(message);
        return;
    }
    //是当前窗口对应的聊天对象
    addRecvBox(message.text,recvUsers[message.fromUserUid].getAvatar());
    message.isRead = 1;
    emit saveToMessageBox(message);
}

//新增发送框
void ChatForm::addSendBox(QString text)
{
    SendBox *sendBox = new SendBox(nowBoxList);
    sendBox->setBackgroundColor(QColor(0,153,255));
    sendBox->setBordetRadius(10);
    sendBox->setTextColor(Qt::white);
    sendBox->setText(text);
    sendBox->setAvatar(sendUser.getAvatar());
    nowBoxList->addWidget(sendBox);
    QTimer::singleShot(100, this, [this]() {//100ms后将垂直滚动条滑到最下面
        nowBoxList->scrollToBottom();
    });
}
//新增接收框
void ChatForm::addRecvBox(QString text, QPixmap Avatar)
{
    RecvBox *recvBox = new RecvBox(nowBoxList);
    recvBox->setBackgroundColor(QColor(255,255,255));
    recvBox->setBordetRadius(10);
    recvBox->setTextColor(Qt::black);
    recvBox->setText(text);
    recvBox->setAvatar(Avatar);
    nowBoxList->addWidget(recvBox);
    QTimer::singleShot(100, this, [this]() {//100ms后将垂直滚动条滑到最下面
        nowBoxList->scrollToBottom();
    });
}

void ChatForm::onMessageBoxPass(MessageBox *messageBox)
{
    //加载用户
    if(sendUser.getUID()==-1 || sendUser.getUID()!=messageBox->uid)
        sendUser = UserGroupManager::getUser(messageBox->uid);
    toId = messageBox->id,chatType = messageBox->chatType;

    //加载聊天成员
    initRecvUsers(toId,chatType);
    ui->nameLabel->setText(messageBox->name);

    //加载消息
    if(messageBoxMap.find(qMakePair(toId,chatType)) == messageBoxMap.end())
    {
        //新建nowBoxList
        nowBoxList = new BoxList(this);
        messageBoxMap.insert(qMakePair(toId,chatType),nowBoxList);
        ui->stackedWidget->addWidget(nowBoxList);
    }
    nowBoxList = messageBoxMap[qMakePair(messageBox->id,messageBox->chatType)];
    ui->stackedWidget->setCurrentWidget(nowBoxList);

    //载入未加载到BoxList里的消息
    int messagesSize = messageBox->messages.size();
    for(int i=messageBox->numUnread;i>=1 && messagesSize-i >= 0;--i){
        Message v = messageBox->messages[messagesSize-i];
        if(v.fromUserUid == sendUser.getUID())
        {
            addSendBox(v.text);
        }else{
            addRecvBox(v.text,recvUsers[v.fromUserUid].getAvatar());
        }
    }
    messageBox->setNumUnread(0);//清空未读消息条数
}

