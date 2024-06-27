#ifndef MAINWIDOW_H
#define MAINWIDOW_H

#include <QWidget>
#include "boxList/messageboxlist.h"
#include "smallWidget/sidebar.h"
#include "chat/chatform.h"
#include <QStackedWidget>
#include "smallWidget/addform.h"

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

    Sidebar *sidebar;
    QStackedWidget *stackedWidget;
    ChatForm *chatForm;
    AddForm *addForm;

    MessageBoxList *messageBoxList;

private slots:
    void showMessages();
    void showFriends();
    void showGroups();
    void showAddForm(); // 新增槽函数声明

signals:
};

#endif // MAINWIDOW_H
