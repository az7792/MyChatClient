#ifndef USERAUTHWINDOW_H
#define USERAUTHWINDOW_H

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>
#include "smallWidget/loginform.h"
#include "smallWidget/registerform.h"
#include "smallWidget/resetpasswordform.h"

class UserAuthWindow : public QWidget
{
    Q_OBJECT
public:
    explicit UserAuthWindow(QWidget *parent = nullptr);

private slots:
    void showLoginForm();
    void showRegisterForm();
    void showResetPasswordForm();
signals:
    void loggedIn(User user);

private:
    QStackedWidget *stackedWidget;
    LoginForm *loginForm;
    RegisterForm *registerForm;
    ResetPasswordForm *resetPasswordForm;
};

#endif // USERAUTHWINDOW_H
