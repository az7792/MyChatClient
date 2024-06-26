#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include "manager/usergroupmanager.h"

#include <QWidget>
#include <QFileDialog>
namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();
    void initForm();
signals:
    void showLoginForm(); // 显示登录窗口
    void registered(); // 用户注册成功

private slots:

    void on_userNameLineEdit_editingFinished();

    void on_accountLineEdit_editingFinished();

    void on_passwordLineEdit1_editingFinished();

    void on_showPasswordCheckBox_stateChanged(int state);

    void on_passwordLineEdit2_editingFinished();

    void on_registerPushButton_clicked();

    void on_getCaptchaPushButton_clicked();

    void on_captchaLineEdit_editingFinished();

    void on_returnPushButton_clicked();

    void on_setAvatarPushButton_clicked();

private:
    Ui::RegisterForm *ui;
    int countdown=0; // 倒计时
    bool passwordOk1=false,passwordOk2=false,userNameOk=false,accounOk=false;
};

#endif // REGISTERFORM_H
