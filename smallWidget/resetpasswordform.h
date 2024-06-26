#ifndef RESETPASSWORDFORM_H
#define RESETPASSWORDFORM_H

#include <QWidget>
#include <manager/usergroupmanager.h>
namespace Ui {
class ResetPasswordForm;
}

class ResetPasswordForm : public QWidget
{
    Q_OBJECT

public:
    explicit ResetPasswordForm(QWidget *parent = nullptr);
    ~ResetPasswordForm();
    void initForm();
signals:
    void showLoginForm(); // 显示登录窗口
private slots:
    void on_accountLineEdit_editingFinished();

    void on_captchaLineEdit_editingFinished();

    void on_returnPushButton_clicked();

    void on_getCaptchaPushButton_clicked();

    void on_resetPasswordPushButton_clicked();

    void on_showPasswordCheckBox_stateChanged(int state);


    void on_passwordLineEdit1_editingFinished();

    void on_passwordLineEdit2_editingFinished();

private:
    Ui::ResetPasswordForm *ui;
    int countdown;
    bool passwordOk1=false,passwordOk2=false,accounOk=false;
};

#endif // RESETPASSWORDFORM_H
