#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>
#include "entity/message.h"
#include <QVector>
#include <QMouseEvent>
namespace Ui {
class MessageBox;
}

class MessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit MessageBox(QWidget *parent = nullptr);
    ~MessageBox();
    void mousePressEvent(QMouseEvent *event) override;//重写鼠标单击事件
    void enterEvent(QEnterEvent *event) override; // 重写鼠标进入事件
    void leaveEvent(QEvent *event) override; // 重写鼠标离开事件
    QVector<Message>messages;//消息列表
    QDateTime time;
    int numUnread;//未读消息数
    QString newMessage;
    QString name;//聊天对象的昵称，用户名 or 群名
    QString chatType;//"user" or "group"
    QPixmap avatar;//聊天对象的头像
    int id;//聊天对象的id，uid or groupid
    int uid;

    void addMessage(Message message);//添加新消息

    void setTime(const QDateTime &newTime);//设置时间
    void setNumUnread(int newNumUnread);//设置未读消息条数
    void setNewMessage(const QString &newNewMessage);//设置显示最新消息
    void setName(const QString &newName);//设置名称
    void setChatType(const QString &newChatType);//设置聊天类型
    void setAvatar(const QPixmap &newAvatar);//设置头像
    void setId(int newId);//设置id
    void setBackgroundColor(const QColor& backgroundcolor);//设置背景颜色
signals:
    void clicked(MessageBox *messageBox);
private:
    Ui::MessageBox *ui;

};

#endif // MESSAGEBOX_H
