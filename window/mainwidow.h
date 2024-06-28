#ifndef MAINWIDOW_H
#define MAINWIDOW_H

#include <QWidget>
#include "boxList/messageboxlist.h"
#include "boxList/friendboxlist.h"
#include "boxList/groupboxlist.h"
#include "smallWidget/sidebar.h"
#include "chat/chatform.h"
#include "smallWidget/userinfoeditdialog.h"
#include <QStackedWidget>
#include "smallWidget/addform.h"
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

    Sidebar *sidebar;
    QStackedWidget *stackedWidget;
    ChatForm *chatForm;
    AddForm *addForm;

    MessageBoxList *messageBoxList;
    FriendBoxList *friendBoxList;
    GroupBoxList *groupBoxList;

private slots:
    void showMessages();
    void showFriends();
    void showGroups();
    void showAddForm(); // 新增槽函数声明
    void showSetting(QPoint pos);

signals:
    void logout();
};

#endif // MAINWIDOW_H
