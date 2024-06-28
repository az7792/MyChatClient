#ifndef FRIENDBOX_H
#define FRIENDBOX_H

#include <QWidget>
#include <QMouseEvent>
#include "entity/user.h"
#include "entity/group.h"
namespace Ui {
class FriendBox;
}

class FriendBox : public QWidget
{
    Q_OBJECT

public:
    explicit FriendBox(QWidget *parent = nullptr);
    explicit FriendBox(User user, QWidget *parent = nullptr);
    explicit FriendBox(Group group, QWidget *parent = nullptr);
    ~FriendBox();
    void mousePressEvent(QMouseEvent *event) override;//重写鼠标单击事件
    void enterEvent(QEnterEvent *event) override; // 重写鼠标进入事件
    void leaveEvent(QEvent *event) override; // 重写鼠标离开事件

    QString name;//聊天对象的昵称，用户名 or 群名
    QString chatType;//"user" or "group"
    QPixmap avatar;//聊天对象的头像
    int id;//聊天对象的id，uid or groupid

    void setName(const QString &newName);//设置名称
    void setChatType(const QString &newChatType);//设置聊天类型
    void setAvatar(const QPixmap &newAvatar);//设置头像
    void setId(int newId);//设置id
    void setBackgroundColor(const QColor& backgroundcolor);//设置背景颜色

signals:
    void clicked(FriendBox *friendBox);
private:
    Ui::FriendBox *ui;
};

#endif // FRIENDBOX_H
