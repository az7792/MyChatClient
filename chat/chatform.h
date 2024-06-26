#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>
#include "entity/user.h"
#include "entity/message.h"
#include "chat/chatwebsocket.h"
#include "smallWidget/sendbox.h"
#include "smallWidget/recvbox.h"
#include "smallWidget/messagebox.h"
#include<QScrollBar>
#include <QMap>
#include <manager/usergroupmanager.h>
namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = nullptr);
    ~ChatForm();
    ChatWebSocket &chatWebsocket = ChatWebSocket::getInstance();
    //void initChat(User fromUser,int toId,QString chatType);
    int toId=-1;//接受者id
    QString chatType;//聊天类型
    User sendUser;
    QMap<int,User> recvUsers;//key(uid),value(User)

    void initRecvUsers(int id,QString chatType);//初始化接收用户列表
signals:
    void saveToMessageBox(Message message);
public slots:
    void onMessageBoxPass(MessageBox *messageBox);
private slots:
    void on_SendPushButton_clicked();
    void onTextMessageReceived(const QString &message);    

private:
    Ui::ChatForm *ui;
    void addSendBox(QString text);
    void addRecvBox(QString text,QPixmap Avatar);
};

#endif // CHATFORM_H
