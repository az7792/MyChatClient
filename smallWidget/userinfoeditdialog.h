#ifndef USERINFOEDITDIALOG_H
#define USERINFOEDITDIALOG_H

#include <QWidget>
#include "manager/usergroupmanager.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
namespace Ui {
class UserInfoEditDialog;
}

class UserInfoEditDialog : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfoEditDialog(QWidget *parent = nullptr);
    ~UserInfoEditDialog();
    void setUser(User user);
protected:
    void closeEvent(QCloseEvent *event) override;
signals:
    void editSuccess();
    void widgetClosed();
private slots:

    void on_userNameLineEdit_editingFinished();

    void on_accountLineEdit_editingFinished();

    void on_passwordLineEdit1_editingFinished();

    void on_showPasswordCheckBox_stateChanged(int state);

    void on_passwordLineEdit2_editingFinished();

    void on_getCaptchaPushButton_clicked();

    void on_captchaLineEdit_editingFinished();

    void on_setAvatarPushButton_clicked();

    void on_editPushButton_clicked();

private:
    Ui::UserInfoEditDialog *ui;
    User user;
    int countdown=0; // 倒计时
    bool passwordOk1=false,passwordOk2=false,userNameOk=true,accounOk=true;

};

#endif // USERINFOEDITDIALOG_H
