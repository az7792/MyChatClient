#include "manager/usergroupmanager.h"
#include <QApplication>
#include <QScrollArea>
#include <cassert>
#include <smallWidget/loginform.h>
#include <smallWidget/registerform.h>
#include <smallWidget/resetpasswordform.h>
#include <window/userauthwindow.h>
#include <smallWidget/recvbox.h>
#include <smallWidget/sendbox.h>
#include <smallWidget/messagebox.h>
#include <chat/chatform.h>
#include <chat/chatwebsocket.h>
#include<boxList/boxlist.h>
#include<smallWidget/sidebar.h>
#include<window/mainwidow.h>
#include <smallWidget/friendbox.h>
#include <boxList/friendboxlist.h>
#include <boxList/groupboxlist.h>
#include <QVector>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     MainWindow mw;
     mw.show();
     mw.setUser(UserGroupManager::getUser(1));
    //FriendBox *fb = new FriendBox(UserGroupManager::getUser(1));
   // fb->show();
    //FriendBox *fbb = new FriendBox(UserGroupManager::getGroupByGid(20));
    //fbb->show();
    // FriendBoxList *fbl = new FriendBoxList(nullptr);
    // QVector<int>ids = UserGroupManager::getUidsByUid(1);
    // fbl->updataFriendBoxsByIds(ids);
    // fbl->show();

    // GroupBoxList *gbl = new GroupBoxList(nullptr);
    // QVector<int>gids = UserGroupManager::getGidsByUid(1);
    // gbl->updataGroupBoxsByIds(gids);
    // gbl->show();
    return a.exec();
    /*/------------测试------------------
    //测试邮箱是否存在
    assert(UserGroupManager::isEmailExist("1460014874@qq.com")==true);
    assert(UserGroupManager::isEmailExist("1460014874@qq.commmmm")==false);
    //测试用户是否存在
    assert(UserGroupManager::isUserExist(1)==true);
    assert(UserGroupManager::isUserExist(11111)==false);
    //测试群是否存在
    assert(UserGroupManager::isGroupExist(20)==true);
    assert(UserGroupManager::isGroupExist(11111)==false);
    //测试登录
    assert(UserGroupManager::login(1,"az77927792")==true);
    assert(UserGroupManager::login(1,"az7792779")==false);
    assert(UserGroupManager::login("1460014874@qq.com","az77927792")==true);
    assert(UserGroupManager::login("1460014874@qq.com","az7792779")==false);
    qDebug()<<"测试通过";
    //------------测试------------------*/
    //Formmanager w;
    //LoginForm w;
    //RegisterForm w;
    //ResetPasswordForm w;
    //UserAuthWindow w;
    ChatWebSocket &websocket = ChatWebSocket::getInstance();
    // QScrollArea *scrollArea = new QScrollArea;
    // QWidget *contentWidget = new QWidget;
    // QVBoxLayout *layout = new QVBoxLayout;
    /*
     * 结构：
     *   QScrollArea
     *   └── QWidget
     *       └── QVBoxLayout
     *           ├── RecvBox
     *           └── SendBox
     */

    // RecvBox *w = new RecvBox;
    // w->setAvatar(QPixmap(":/img/resources/img/defaultAvatar.jpg"));
    // w->setText("你好");
    // w->setTextColor(Qt::red);
    // w->setBackgroundColor(Qt::blue);
    // w->setBordetRadius(10);

    // SendBox *ww = new SendBox;
    // ww->setAvatar(QPixmap(":/img/resources/img/logo.png"));
    // ww->setText("aushuaihioaioaios阿松符号是佛啊爱哦手癌哈佛奥i哈佛i安徽佛啊hi发爱上哈佛i啊hi哦好i和");

    //
    Sidebar *www = new Sidebar();
    www->show();
    QWidget * widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    widget->setLayout(layout);

    BoxList *boxlist = new BoxList();
    boxlist->show();
    MessageBox *w = new MessageBox();
    MessageBox *ww = new MessageBox();
    layout->addWidget(w);
    layout->addWidget(www);
    layout->addWidget(ww);

    widget->show();
    //boxlist->addWidget(w);
    //boxlist->addWidget(ww);
    w->setId(20);
    w->uid=1;
    websocket.connectToServer(QUrl("ws://localhost:8080/chat/1"));
    w->setChatType("group");
    w->setName("wangyi");
    // w->setAvatar(QPixmap(":/img/resources/img/logo.png"));
    // w->setNewMessage("ahaha34343434343");
    // w->setName("4353444444444444444");
    // w->setNumUnread(3);
    // w->setTime(QDateTime::currentDateTime());
    // w->setBackgroundColor(Qt::red);
    // layout->addWidget(w);
    // layout->addWidget(ww);

    // // 设置布局到内容窗口
    // contentWidget->setLayout(layout);

    // // 将内容窗口设置为 QScrollArea 的内容
    // scrollArea->setWidget(contentWidget);
    // scrollArea->setWidgetResizable(true); // 确保内容窗口可以调整大小以适应 QScrollArea

    // // 显示 QScrollArea
    // scrollArea->show();

    ChatForm *chatForm = new ChatForm();
    QObject::connect(w,&MessageBox::clicked,chatForm,&ChatForm::onMessageBoxPass);
    chatForm->show();

    return a.exec();
}
