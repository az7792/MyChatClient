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
    void onSettingClicked(QPoint pos);
    void onUserAvatarClicked();

private slots:
    void on_messages_clicked();

    void on_friends_clicked();

    void on_groups_clicked();

    void on_setting_clicked();

    void on_userAvatar_clicked();

private:
    Ui::Sidebar *ui;
};

#endif // SIDEBAR_H
