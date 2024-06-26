#include "formmanager.h"
#include "manager/usergroupmanager.h"
#include <QApplication>
#include <cassert>
#include <smallWidget/loginform.h>
#include <smallWidget/registerform.h>
#include <smallWidget/resetpasswordform.h>
#include <window/userauthwindow.h>
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
    UserAuthWindow w;
    w.show();

    return a.exec();
}
