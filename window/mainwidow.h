#ifndef MAINWIDOW_H
#define MAINWIDOW_H

#include <QWidget>
#include "boxList/messageboxlist.h"
#include "smallWidget/sidebar.h"
#include "chat/chatform.h"
#include <QStackedWidget>

class MainWidow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidow(QWidget *parent = nullptr);
    ~MainWidow();
    void setUser(User user);

private:
    User user;
    ChatWebSocket &websocket = ChatWebSocket::getInstance();

    Sidebar *sidebar;//侧边栏
    QStackedWidget *stackedWidget;
    ChatForm *chatForm;//聊天窗口

    MessageBoxList *messageBoxList;//消息控件列表 0
private slots:
    void showMessages();
    void showFriends();
    void showGroups();

signals:
};

#endif // MAINWIDOW_H
