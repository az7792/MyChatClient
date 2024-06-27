#include "addform.h"
#include <QPixmap>
#include <QDebug>
#include "entity/user.h"
#include "entity/group.h" // 假设有一个Group类

AddForm::AddForm(QWidget *parent) : QWidget(parent), userId(0), currentContactWidget(nullptr)
{
    setupUI();
}

void AddForm::setupUI()
{
    // 基本设置
    setWindowTitle("搜索联系人");
    this->setStyleSheet("QWidget { background-color: white; }");
    resize(500, 600);

    // 创建按钮
    findAllButton = new QPushButton("全部", this);
    findUserButton = new QPushButton("用户", this);
    findGroupButton = new QPushButton("群聊", this);

    // 设置按钮样式
    findAllButton->setStyleSheet("QPushButton { background-color: black; color: white; border: 1px solid black; }");
    findUserButton->setStyleSheet("QPushButton { background-color: white; color: black; border: 1px solid black; }");
    findGroupButton->setStyleSheet("QPushButton { background-color: white; color: black; border: 1px solid black; }");

    // 创建搜索框
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("输入搜索关键词");
    searchLineEdit->setClearButtonEnabled(true);
    searchLineEdit->setFixedSize(400, 25);

    // 创建搜索按钮
    searchButton = new QPushButton("搜索", this);
    searchButton->setStyleSheet("QPushButton { background-color: white; color: black; border: 1px solid black; }");

    // 创建搜索提示图片和文字
    searchIconLabel = new QLabel(this);
    QPixmap pixmap(":/img/resources/1.png"); // 确保图像路径正确
    searchIconLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));
    searchHintLabel = new QLabel("输入关键词搜索", this);
    searchHintLabel->setAlignment(Qt::AlignCenter);

    // 设置顶部按钮布局
    QHBoxLayout *topButtonLayout = new QHBoxLayout;
    topButtonLayout->addWidget(findAllButton);
    topButtonLayout->addWidget(findUserButton);
    topButtonLayout->addWidget(findGroupButton);

    // 设置搜索框和按钮布局
    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    // 设置中心内容布局
    QVBoxLayout *centerLayout = new QVBoxLayout;
    centerLayout->addWidget(searchIconLabel);
    centerLayout->addWidget(searchHintLabel);
    centerLayout->setAlignment(Qt::AlignCenter);

    QWidget *centerWidget = new QWidget(this);
    centerWidget->setLayout(centerLayout);

    contentStack = new QStackedWidget(this);
    contentStack->addWidget(centerWidget);

    // 设置主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(searchLayout);
    mainLayout->addLayout(topButtonLayout);
    mainLayout->addWidget(contentStack);

    setLayout(mainLayout);

    // 连接按钮点击事件
    connect(findAllButton, &QPushButton::clicked, this, &AddForm::onFindAllButtonClicked);
    connect(findUserButton, &QPushButton::clicked, this, &AddForm::onFindUserButtonClicked);
    connect(findGroupButton, &QPushButton::clicked, this, &AddForm::onFindGroupButtonClicked);
    connect(searchButton, &QPushButton::clicked, this, &AddForm::onSearchButtonClicked);
}

void AddForm::setUserId(int userId)
{
    this->userId = userId;
}

void AddForm::onFindAllButtonClicked()
{
    status = 0;
    updatePlaceholderText();
    findAllButton->setStyleSheet("QPushButton { background-color: black; color: white; border: 1px solid black; }");
    findUserButton->setStyleSheet("QPushButton { background-color: white; color: black; border: 1px solid black; }");
    findGroupButton->setStyleSheet("QPushButton { background-color: white; color: black; border: 1px solid black; }");

    searchIconLabel->show();
    searchHintLabel->show();

    clearPreviousSearchResult();
    searchLineEdit->clear();
}

void AddForm::onFindUserButtonClicked()
{
    status = 1;
    updatePlaceholderText();
    findUserButton->setStyleSheet("QPushButton { background-color: black; color: white; border: 1px solid black; }");
    findAllButton->setStyleSheet("QPushButton { background-color: white; color: black; border: 1px solid black; }");
    findGroupButton->setStyleSheet("QPushButton { background-color: white; color: black; border: 1px solid black; }");

    searchIconLabel->show();
    searchHintLabel->show();

    clearPreviousSearchResult();
    searchLineEdit->clear();
}

void AddForm::onFindGroupButtonClicked()
{
    status = 2;
    updatePlaceholderText();
    findGroupButton->setStyleSheet("QPushButton { background-color: black; color: white; border: 1px solid black; }");
    findUserButton->setStyleSheet("QPushButton { background-color: white; color: black; border: 1px solid黑; }");
    findAllButton->setStyleSheet("QPushButton { background-color: white; color: black; border: 1px solid黑; }");

    searchIconLabel->show();
    searchHintLabel->show();

    clearPreviousSearchResult();
    searchLineEdit->clear();
}

void AddForm::onSearchButtonClicked()
{
    QString searchText = searchLineEdit->text();
    //qDebug() << "搜索: " << searchText;

    clearPreviousSearchResult();

    if (status == 1) {
        int userID = searchText.toInt();
        if (UserGroupManager::isUserExist(userID)) {
            User user = UserGroupManager::getUser(userID);
            displayUser(user);
        } else {
            QLabel *notFoundLabel = new QLabel("User not found", this);
            notFoundLabel->setAlignment(Qt::AlignCenter);
            contentStack->addWidget(notFoundLabel);
            contentStack->setCurrentWidget(notFoundLabel);
        }
    } else if (status == 2) {
        int groupID = searchText.toInt();
        if (UserGroupManager::isGroupExist(groupID)) {
            Group group = UserGroupManager::getGroupByGid(groupID);
            displayGroup(group);
        } else {
            QLabel *notFoundLabel = new QLabel("Group not found", this);
            notFoundLabel->setAlignment(Qt::AlignCenter);
            contentStack->addWidget(notFoundLabel);
            contentStack->setCurrentWidget(notFoundLabel);
        }
    } else {
        int userID = searchText.toInt();
        int groupID = searchText.toInt();

        bool isUserExist = UserGroupManager::isUserExist(userID);
        bool isGroupExist = UserGroupManager::isGroupExist(groupID);

        clearPreviousSearchResult();

        if (isUserExist&&!isGroupExist) {
            User user = UserGroupManager::getUser(userID);
            displayUser(user);
        }

        if (isGroupExist&&!isUserExist) {
            Group group = UserGroupManager::getGroupByGid(groupID);
            displayGroup(group);
        }

        if (!isUserExist && !isGroupExist) {
            QLabel *notFoundLabel = new QLabel("User or Group not found", this);
            notFoundLabel->setAlignment(Qt::AlignCenter);
        }

        if(isUserExist&&isGroupExist)
        {
            User user = UserGroupManager::getUser(userID);
            Group group = UserGroupManager::getGroupByGid(groupID);
            displayGroupandUser(group,user);
        }
    }

    searchIconLabel->hide();
    searchHintLabel->hide();
}

void AddForm::updatePlaceholderText()
{
    if (status == 0) {
        searchLineEdit->setPlaceholderText("输入搜索关键词");
    } else if (status == 1) {
        searchLineEdit->setPlaceholderText("UserId");
    } else if (status == 2) {
        searchLineEdit->setPlaceholderText("GroupId");
    }
}

void AddForm::clearPreviousSearchResult()
{
    if (currentContactWidget != nullptr) {
        contentStack->removeWidget(currentContactWidget);
        currentContactWidget->deleteLater();
        currentContactWidget = nullptr;

        contentStack->setCurrentIndex(0);
        searchIconLabel->show();
        searchHintLabel->show();
    } else {
        contentStack->setCurrentIndex(0);
        searchIconLabel->show();
        searchHintLabel->show();
    }
}
void AddForm::displayUser(User &user)
{
    // 创建一个新的 QWidget，用于显示用户信息
    QWidget *userWidget = new QWidget(this);
    QHBoxLayout *userLayout = new QHBoxLayout(userWidget);

    // 显示用户头像
    QLabel *avatarLabel = new QLabel(userWidget);
    QPixmap avatar = user.getAvatar();
    avatarLabel->setPixmap(avatar.scaled(80, 80, Qt::KeepAspectRatio));
    userLayout->addWidget(avatarLabel);

    // 显示用户名
    QLabel *nameLabel = new QLabel(user.getUsername(), userWidget);
    nameLabel->setAlignment(Qt::AlignCenter);
    userLayout->addWidget(nameLabel);

    // 添加一个按钮
    QPushButton *addButton = new QPushButton("添加", userWidget);
    connect(addButton, &QPushButton::clicked, [=]() {
        qDebug() << "添加按钮被点击";
        // 可以在这里实现用户添加操作
        // // 准备要发送的数据
        // QUrlQuery postData;
        // postData.addQueryItem("uid1", QString::number(user.)); // 替换为实际的用户ID
        // postData.addQueryItem("uid2", QString::number(userId2)); // 替换为实际的用户ID

        // // 发送 POST 请求并获取响应
        // QJsonDocument responseJson = UserGroupManager::sendPostRequest("/contacts/add", postData);

        // // 处理响应
        // if (!responseJson.isEmpty()) {
        //     qDebug() << "添加用户操作成功：" << responseJson.toJson();
        //     // 在这里处理成功的逻辑，可以更新界面或者显示成功信息
        // } else {
        //     qDebug() << "添加用户操作失败";
        //     // 在这里处理失败的逻辑，可以显示错误信息给用户
        // }
    });
    userLayout->addWidget(addButton);

    // 设置 QWidget 的布局为水平布局
    userWidget->setLayout(userLayout);

    // 将该用户信息的 QWidget 添加到 contentStack 中
    contentStack->addWidget(userWidget);

    // 设置 contentStack 当前显示的 Widget 为该用户信息的 QWidget
    contentStack->setCurrentWidget(userWidget);

    // 更新当前联系人的 Widget 为该用户信息的 QWidget
    currentContactWidget = userWidget;
}

void AddForm::displayGroup(Group &group)
{
    // 创建一个新的 QWidget，用于显示群组信息
    QWidget *groupWidget = new QWidget(this);
    QHBoxLayout *groupLayout = new QHBoxLayout(groupWidget);

    // 显示群组头像
    QLabel *avatarLabel = new QLabel(groupWidget);
   QPixmap avatar = group.getAvatar();
    avatarLabel->setPixmap(avatar.scaled(80, 80, Qt::KeepAspectRatio));
    groupLayout->addWidget(avatarLabel);

    // 显示群组名
    QLabel *nameLabel = new QLabel(group.getGroupname(), groupWidget);
    nameLabel->setAlignment(Qt::AlignCenter);
    groupLayout->addWidget(nameLabel);

    // 添加一个按钮
    QPushButton *addButton = new QPushButton("添加", groupWidget);
    connect(addButton, &QPushButton::clicked, [=]() {
        qDebug() << "添加按钮被点击";
        // 可以在这里实现添加群组操作
    });
    groupLayout->addWidget(addButton);

    // 设置 QWidget 的布局为水平布局
    groupWidget->setLayout(groupLayout);

    // 将该群组信息的 QWidget 添加到 contentStack 中
    contentStack->addWidget(groupWidget);

    // 设置 contentStack 当前显示的 Widget 为该群组信息的 QWidget
    contentStack->setCurrentWidget(groupWidget);

    // 更新当前联系人的 Widget 为该群组信息的 QWidget
    currentContactWidget = groupWidget;
}
void AddForm::displayGroupandUser(Group &group, User &user)
{
    // 创建一个新的 QWidget，用于显示群组和用户信息
    QWidget *groupUserWidget = new QWidget(this);
    QVBoxLayout *groupUserLayout = new QVBoxLayout(groupUserWidget);

    // 显示群组信息
    QWidget *groupWidget = new QWidget(this);
    QHBoxLayout *groupLayout = new QHBoxLayout(groupWidget);

    QLabel *groupAvatarLabel = new QLabel(groupWidget);
    QPixmap groupAvatar = group.getAvatar();
    groupAvatarLabel->setPixmap(groupAvatar.scaled(80, 80, Qt::KeepAspectRatio));
    groupLayout->addWidget(groupAvatarLabel);

    QLabel *groupNameLabel = new QLabel(group.getGroupname(), groupWidget);
    groupNameLabel->setAlignment(Qt::AlignCenter);
    groupLayout->addWidget(groupNameLabel);

    QPushButton *groupAddButton = new QPushButton("添加", groupWidget);
    connect(groupAddButton, &QPushButton::clicked, [=]() {
        qDebug() << "添加群组按钮被点击";
        // 实现添加群组操作
    });
    groupLayout->addWidget(groupAddButton);

    groupWidget->setLayout(groupLayout);
    groupUserLayout->addWidget(groupWidget);

    // 显示用户信息
    QWidget *userWidget = new QWidget(this);
    QHBoxLayout *userLayout = new QHBoxLayout(userWidget);

    QLabel *userAvatarLabel = new QLabel(userWidget);
    QPixmap userAvatar = user.getAvatar();
    userAvatarLabel->setPixmap(userAvatar.scaled(80, 80, Qt::KeepAspectRatio));
    userLayout->addWidget(userAvatarLabel);

    QLabel *userNameLabel = new QLabel(user.getUsername(), userWidget);
    userNameLabel->setAlignment(Qt::AlignCenter);
    userLayout->addWidget(userNameLabel);

    QPushButton *userAddButton = new QPushButton("添加", userWidget);
    connect(userAddButton, &QPushButton::clicked, [=]() {
        qDebug() << "添加用户按钮被点击";
        // 实现添加用户操作
    });
    userLayout->addWidget(userAddButton);

    userWidget->setLayout(userLayout);
    groupUserLayout->addWidget(userWidget);

    groupUserWidget->setLayout(groupUserLayout);

    // 将整个组合部件添加到 contentStack 中
    contentStack->addWidget(groupUserWidget);

    // 设置 contentStack 当前显示的 Widget 为整个组合部件
    contentStack->setCurrentWidget(groupUserWidget);

    // 更新当前联系人的 Widget 为最后添加的用户信息的 QWidget
    currentContactWidget = userWidget; // 这里可以根据实际情况选择 groupWidget 或 userWidget
}
