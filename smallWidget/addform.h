#ifndef ADDFORM_H
#define ADDFORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <manager/usergroupmanager.h>

class AddForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddForm(QWidget *parent = nullptr);
    void setUserId(int userId);
    int status = 0;

private slots:
    void onFindAllButtonClicked();
    void onFindUserButtonClicked();
    void onFindGroupButtonClicked();
    void onSearchButtonClicked();

private:
    void setupUI();
    void updatePlaceholderText();
    void clearPreviousSearchResult();
    void displayUser(User &user);
    void displayGroup(Group &group);
    void displayGroupandUser(Group &group,User &user);

    int userId; // 保存当前用户ID

    QPushButton *findAllButton;
    QPushButton *findUserButton;
    QPushButton *findGroupButton;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QLabel *searchIconLabel;
    QLabel *searchHintLabel;
    QStackedWidget *contentStack;
    QVBoxLayout *resultLayout; // 用于显示搜索结果的布局
    QWidget *currentContactWidget; // 当前显示的搜索结果 widget
};

#endif // ADDFORM_H
