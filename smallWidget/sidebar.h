#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

namespace Ui {
class Sidebar;
}

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = nullptr);
    ~Sidebar();
    void setAvatar(QPixmap Avatar);

signals:
    void onMessagesClicked();
    void onFriendsClicked();
    void onGroupsClicked();
    void onSettingClicked();
    void onUserAvatarClicked();
    void onAddClicked(); // 新增信号声明

private slots:
    void on_messages_clicked();
    void on_friends_clicked();
    void on_groups_clicked();
    void on_setting_clicked();
    void on_userAvatar_clicked();
    void on_add_clicked();

private:
    Ui::Sidebar *ui;
};

#endif // SIDEBAR_H
