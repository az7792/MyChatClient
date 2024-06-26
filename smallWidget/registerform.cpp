#include "registerform.h"
#include "ui_registerform.h"

#include <QMessageBox>

RegisterForm::RegisterForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

void RegisterForm::initForm()
{
    ui->avatarLabel->setPixmap(QPixmap(":/img/resources/img/defaultAvatar.jpg"));

    ui->userNameTipLabel->clear();
    ui->userNameLineEdit->clear();

    ui->accountdTipLabel->clear();
    ui->accountLineEdit->clear();

    ui->passwordTipLabel1->clear();
    ui->passwordLineEdit1->clear();

    ui->passwordTipLabel2->clear();
    ui->passwordLineEdit2->clear();

    ui->captchaTipLabel->clear();
    ui->captchaLineEdit->clear();

    ui->showPasswordCheckBox->setChecked(false);
}


// 用户名编辑框输入完毕后判断格式
void RegisterForm::on_userNameLineEdit_editingFinished()
{
    QString text = ui->userNameLineEdit->text();
    if(UserGroupManager::isUsernameValid(text)){
        ui->userNameTipLabel->setText("");
        userNameOk = true;
    }else{
        ui->userNameTipLabel->setText("用户名由1到20个汉字、字母、数字或下划线组成");
        userNameOk = false;
    }
}

// 账号(email)编辑框输入完毕后判断格式
void RegisterForm::on_accountLineEdit_editingFinished()
{
    QString text = ui->accountLineEdit->text();
    if(!UserGroupManager::isEmailValid(text)){
        ui->accountdTipLabel->setText("邮箱格式错误");
        accounOk = false;
        return;
    }
    if(UserGroupManager::isEmailExist(text)){
        ui->accountdTipLabel->setText("此邮箱已注册过");
        accounOk = false;
        return;
    }
    ui->accountdTipLabel->setText("");
    accounOk = true;
}

// 密码1编辑框输入完毕后判断格式
void RegisterForm::on_passwordLineEdit1_editingFinished()
{
    on_passwordLineEdit2_editingFinished();
    QString text1 = ui->passwordLineEdit1->text();
    if(!UserGroupManager::isPasswordValid(text1)){
        ui->passwordTipLabel1->setText("密码长度应为6-20个字符，并且必须包含以下四种类型中的至少两种：大写字母、小写字母、数字、特殊符号");
        passwordOk1 = false;
        return;
    }
    ui->passwordTipLabel1->setText("");
    passwordOk1 = true;
}

// 切换是否显示密码
void RegisterForm::on_showPasswordCheckBox_stateChanged(int state)
{
    if(state == Qt::Checked) {
        ui->passwordLineEdit1->setEchoMode(QLineEdit::Normal);
        ui->passwordLineEdit2->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordLineEdit1->setEchoMode(QLineEdit::Password);
        ui->passwordLineEdit2->setEchoMode(QLineEdit::Password);
    }
}

// 密码2编辑框输入完毕后判断格式
void RegisterForm::on_passwordLineEdit2_editingFinished()
{
    QString text1 = ui->passwordLineEdit1->text();
    QString text2 = ui->passwordLineEdit2->text();
    if(text1==text2){
        ui->passwordTipLabel2->setText("");
        passwordOk2 = true;
    }else{
        ui->passwordTipLabel2->setText("两次密码不一致");
        passwordOk2 = false;
    }

}

// 用户注册请求
void RegisterForm::on_registerPushButton_clicked()
{
    if(!(passwordOk1&&passwordOk2&&userNameOk&&accounOk)){
        QMessageBox::warning(this,"","注册失败,请检查信息是否填写错误");
        return;
    }
    bool success = false;
    QString username = ui->userNameLineEdit->text();
    QString email = ui->accountLineEdit->text();
    QString password = ui->passwordLineEdit1->text();
    QString captcha = ui->captchaLineEdit->text();
    if(captcha.size()!=6||!UserGroupManager::matchCaptcha(email,captcha)){
        QMessageBox::warning(this,"","注册失败,验证码错误");
        return;
    }
    success = UserGroupManager::registerUser(username,email,password,ui->avatarLabel->pixmap());
    if(success){
        emit registered();
        QMessageBox::information(this, "注册成功", "注册成功");
    }else{
        QMessageBox::warning(this, "注册失败", "注册失败，请重试");
    }
}

//获取验证码
void RegisterForm::on_getCaptchaPushButton_clicked()
{
    if(!accounOk){
        QMessageBox::warning(this,"","邮箱错误");
        return;
    }
    // 禁用按钮并开始60秒倒计时
    ui->getCaptchaPushButton->setEnabled(false); // 禁用按钮
    ui->getCaptchaPushButton->setText("60s"); // 初始化按钮文本为60s

    QTimer *timer = new QTimer(this);
    countdown = 60;

    // lambda函数更新按钮文本
    auto updateButton = [this, timer]() mutable {
        if (countdown > 0) {
            ui->getCaptchaPushButton->setText(QString::number(countdown) + "s");
            (countdown)--;
        } else {
            timer->stop();
            ui->getCaptchaPushButton->setText("获取验证码");
            ui->getCaptchaPushButton->setEnabled(true);
            timer->deleteLater();
        }
    };

    // 连接定时器的timeout信号到lambda函数
    connect(timer, &QTimer::timeout, updateButton);

    // 启动定时器，每秒触发一次timeout信号
    timer->start(1000);

    bool getCaptcha = UserGroupManager::getCaptchaByEmail(ui->accountLineEdit->text());
    if(!getCaptcha){
        qDebug()<<"获取验证失败";
        timer->stop();
        ui->getCaptchaPushButton->setText("获取验证码");
        ui->getCaptchaPushButton->setEnabled(true); // 重新启用按钮
        timer->deleteLater(); // 删除QTimer对象
        return;
    }
}


void RegisterForm::on_captchaLineEdit_editingFinished()
{
    QString captcha = ui->captchaLineEdit->text();
    if(captcha.size()!=6)
        ui->captchaTipLabel->setText("验证码长度应为6");
    else
        ui->captchaTipLabel->setText("");
}


void RegisterForm::on_returnPushButton_clicked()
{
    emit showLoginForm();
}


void RegisterForm::on_setAvatarPushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择图片", "", "图片文件 (*.png *.jpg *.jpeg)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.size() > 512 * 1024) { // 文件大小超过 515KB
            QMessageBox::warning(this, "警告", "图片大小不能超过512KB");
            return;
        }
        QPixmap pixmap(filePath);
        if (!pixmap.isNull()) {
            ui->avatarLabel->setPixmap(pixmap.scaled(ui->avatarLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            ui->avatarLabel->setText("无法加载图片");
        }
    }
}

