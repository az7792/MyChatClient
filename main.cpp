#include "formmanager.h"
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
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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

    QScrollArea *scrollArea = new QScrollArea;
    QWidget *contentWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
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
    MessageBox *w = new MessageBox();
    MessageBox *ww = new MessageBox();
    w->setAvatar(QPixmap(":/img/resources/img/logo.png"));
    w->setNewMessage("ahaha34343434343");
    w->setName("4353444444444444444");
    w->setNumUnread(3);
    w->setTime(QDateTime::currentDateTime());
    w->setBackgroundColor(Qt::red);
    layout->addWidget(w);
    layout->addWidget(ww);

    // 设置布局到内容窗口
    contentWidget->setLayout(layout);

    // 将内容窗口设置为 QScrollArea 的内容
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true); // 确保内容窗口可以调整大小以适应 QScrollArea

    // 显示 QScrollArea
    scrollArea->show();
    return a.exec();
}
