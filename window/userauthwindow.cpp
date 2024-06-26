#include "userauthwindow.h"

UserAuthWindow::UserAuthWindow(QWidget *parent)
    : QWidget{parent}
{
    stackedWidget = new QStackedWidget(this);
    loginForm = new LoginForm(this);
    registerForm = new RegisterForm(this);
    resetPasswordForm = new ResetPasswordForm(this);

    // 添加子窗口到QStackedWidget
    stackedWidget->addWidget(loginForm);//0
    stackedWidget->addWidget(registerForm);//1
    stackedWidget->addWidget(resetPasswordForm);//2

    //连接信号与槽函数
    connect(loginForm,&LoginForm::loggedIn,this,&UserAuthWindow::loggedIn);//登录成功后发出登录成功的信号
    connect(loginForm,&LoginForm::showRegisterForm,this,&UserAuthWindow::showRegisterForm);//登录窗口按下注册按钮后切换到注册窗口
    connect(loginForm,&LoginForm::showResetPasswordForm,this,&UserAuthWindow::showResetPasswordForm);//登录窗口按下找回密码按钮后切换到找回密码窗口
    connect(registerForm,&RegisterForm::showLoginForm,this,&UserAuthWindow::showLoginForm);//注册窗口按下返回后切换到登录窗口
    connect(resetPasswordForm,&ResetPasswordForm::showLoginForm,this,&UserAuthWindow::showLoginForm);//找回密码窗口按下返回后切换到登录窗口

    //布局
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(stackedWidget);
    this->setLayout(layout);
    setMaximumWidth(500);
    setWindowTitle("用户认证");
}

void UserAuthWindow::showLoginForm() {
    stackedWidget->setCurrentWidget(loginForm);
    loginForm->initForm();
}

void UserAuthWindow::showRegisterForm() {
    stackedWidget->setCurrentWidget(registerForm);
    registerForm->initForm();
}

void UserAuthWindow::showResetPasswordForm() {
    stackedWidget->setCurrentWidget(resetPasswordForm);
    resetPasswordForm->initForm();
}
