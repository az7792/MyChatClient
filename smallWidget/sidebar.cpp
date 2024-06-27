#include "sidebar.h"
#include "ui_sidebar.h"

Sidebar::Sidebar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sidebar)
{
    ui->setupUi(this);
}

Sidebar::~Sidebar()
{
    delete ui;
}

void Sidebar::setAvatar(QPixmap Avatar)
{
    ui->userAvatar->setIcon(QIcon(Avatar));
}

void Sidebar::on_messages_clicked()
{
    emit onMessagesClicked();
}

void Sidebar::on_friends_clicked()
{
    emit onFriendsClicked();
}

void Sidebar::on_groups_clicked()
{
    emit onGroupsClicked();
}

void Sidebar::on_setting_clicked()
{
    emit onSettingClicked(ui->setting->mapToGlobal(ui->setting->rect().bottomRight()));
}

void Sidebar::on_userAvatar_clicked()
{
    emit onUserAvatarClicked();
}

void Sidebar::on_add_clicked()
{
    emit onAddClicked(); // 发射新增的信号
}
