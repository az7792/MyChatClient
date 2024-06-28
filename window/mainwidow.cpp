#include "mainwidow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    // 初始化子控件
    sidebar = new Sidebar(this);
    stackedWidget = new QStackedWidget(this);
    chatForm = new ChatForm(this);
    messageBoxList = new MessageBoxList(this); // 消息控件列表 0
    friendBoxList = new FriendBoxList(this); // 消息控件列表 1
    groupBoxList = new GroupBoxList(this); // 消息控件列表 2

    stackedWidget->addWidget(messageBoxList); // 第0页
    stackedWidget->addWidget(friendBoxList); // 第1页
    stackedWidget->addWidget(groupBoxList); // 第2页
    stackedWidget->setCurrentIndex(0);
    stackedWidget->setMaximumWidth(200);
    stackedWidget->setMinimumWidth(100);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(chatForm);
    mainLayout->setContentsMargins(0, 0, 0, 0); // 与边框的间距
    mainLayout->setSpacing(0);                  // 控件之间的间距

    this->setLayout(mainLayout);
    this->resize(800, 550);

    // 连接信号与槽
    connect(sidebar, &Sidebar::onMessagesClicked, this, &MainWindow::showMessages);
    connect(sidebar, &Sidebar::onFriendsClicked, this, &MainWindow::showFriends);
    connect(sidebar, &Sidebar::onGroupsClicked, this, &MainWindow::showGroups);
    connect(sidebar, &Sidebar::onSettingClicked, this, &MainWindow::showSetting);
    connect(sidebar, &Sidebar::onAddClicked, this, &MainWindow::showAddForm); // 连接添加按钮信号
    // 将ChatForm收到消息转到MessageBoxList
    connect(chatForm, &ChatForm::saveToMessageBox, messageBoxList, &MessageBoxList::updataMessageBox);

    // 从MessageBoxList的某个MessageBox转到ChatForm
    connect(messageBoxList, &MessageBoxList::passMessageBox, chatForm, &ChatForm::onMessageBoxPass);

    // 从FriendBoxList的某个FriendBox转到匿名函数
    connect(friendBoxList,&FriendBoxList::passFriendBox,this,[=](FriendBox *friendBox){
        showMessages();
        if(messageBoxList->hasMessageBox(qMakePair(friendBox->id,friendBox->chatType)))
            return;
        User tmpUser = UserGroupManager::getUser(friendBox->id);
        MessageBox * newMessageBox = messageBoxList->getMessageBoxByUser(tmpUser);
        messageBoxList->addMessageBox(newMessageBox);
    });

    // 从GroupBoxList的某个FriendBox转到匿名函数
    connect(groupBoxList,&GroupBoxList::passFriendBox,this,[=](FriendBox *friendBox){
         showMessages();
        if(messageBoxList->hasMessageBox(qMakePair(friendBox->id,friendBox->chatType)))
            return;
        Group tmpGroup = UserGroupManager::getGroupByGid(friendBox->id);
        MessageBox * newMessageBox = messageBoxList->getMessageBoxByGroup(tmpGroup);
        messageBoxList->addMessageBox(newMessageBox);
    });
}

MainWindow::~MainWindow() {}

void MainWindow::setUser(User user)
{
    this->user = user;
    chatForm->sendUser = this->user;
    messageBoxList->UID = this->user.getUID();
    // 设置头像显示图标
    sidebar->setAvatar(user.getAvatar());

    // 连接websocket服务器
    websocket.connectToServer(QUrl("ws://localhost:8080/chat/" + QString::number(user.getUID())));
    // 连接websocket的信号
}

void MainWindow::showMessages()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::showFriends()
{
    stackedWidget->setCurrentIndex(1);
    QVector<int>ids = UserGroupManager::getUidsByUid(user.getUID());
    friendBoxList->updataFriendBoxsByIds(ids);
}

void MainWindow::showGroups()
{
    stackedWidget->setCurrentIndex(2);
    QVector<int>ids = UserGroupManager::getGidsByUid(user.getUID());
    groupBoxList->updataGroupBoxsByIds(ids);
}

void MainWindow::showAddForm()
{
    AddForm *addForm = new AddForm(); // 创建新的AddForm窗口
    addForm->setUserId(user.getUID());
    addForm->show();                  // 显示新的窗口
}

void MainWindow::showSetting(QPoint pos)
{
    QMenu menu;
    QAction *action1 = menu.addAction("修改个人信息");
    QAction *action2 = menu.addAction("退出");

    connect(&menu, &QMenu::triggered, this, [=](QAction *action)
            {
        if (action == action1) {
            //修改个人信息
            UserInfoEditDialog *userInfoEditDialog = new UserInfoEditDialog();
            userInfoEditDialog->setUser(user);
            userInfoEditDialog->show();
            this->hide();

            // 连接对话框的信号与槽
            connect(userInfoEditDialog, &UserInfoEditDialog::widgetClosed, this, [=](){
                userInfoEditDialog->deleteLater(); // 在对话框关闭后删除
                this->show(); // 显示主窗口
            });

            connect(userInfoEditDialog, &UserInfoEditDialog::editSuccess, this, [=](){
                emit logout();//修改成功后让用户重新登录
            });

        } else if (action == action2) {//退出登录
            emit logout();
        } });

    menu.exec(pos);
}
