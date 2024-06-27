#ifndef MAINWIDOW_H
#define MAINWIDOW_H

#include <QWidget>
#include "boxList/messageboxlist.h"
#include "smallWidget/sidebar.h"
#include "chat/chatform.h"
#include "smallWidget/userinfoeditdialog.h"
#include <QStackedWidget>
#include <QMenu>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
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
    void showSetting(QPoint pos);

signals:
    void logout();
};

#endif // MAINWIDOW_H
