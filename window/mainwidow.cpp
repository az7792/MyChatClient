#include "mainwidow.h"
#include <QDebug>

MainWidow::MainWidow(QWidget *parent)
    : QWidget{parent}
{
    // 初始化子控件
    sidebar = new Sidebar(this);
    stackedWidget = new QStackedWidget(this);
    chatForm = new ChatForm(this);
    messageBoxList = new MessageBoxList(this); // 消息控件列表 0

    stackedWidget->addWidget(messageBoxList); // 第0页
    stackedWidget->setCurrentIndex(0);
    stackedWidget->setMaximumWidth(200);
    stackedWidget->setMinimumWidth(100);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(chatForm);
    mainLayout->setContentsMargins(0, 0, 0, 0); // 与边框的间距
    mainLayout->setSpacing(0); // 控件之间的间距

    this->setLayout(mainLayout);
    this->resize(800, 550);

    // 连接信号与槽
    connect(sidebar, &Sidebar::onMessagesClicked, this, &MainWidow::showMessages);
    connect(sidebar, &Sidebar::onFriendsClicked, this, &MainWidow::showFriends);
    connect(sidebar, &Sidebar::onGroupsClicked, this, &MainWidow::showGroups);
    connect(sidebar, &Sidebar::onAddClicked, this, &MainWidow::showAddForm); // 连接添加按钮信号
    // 将ChatForm收到消息转到MessageBoxList
    connect(chatForm, &ChatForm::saveToMessageBox, messageBoxList, &MessageBoxList::updataMessageBox);
    // 从MessageBoxList的某个MessageBox转到ChatForm
    connect(messageBoxList, &MessageBoxList::passMessageBox, chatForm, &ChatForm::onMessageBoxPass);
}

MainWidow::~MainWidow() {}

void MainWidow::setUser(User user)
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

void MainWidow::showMessages()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWidow::showFriends()
{
    // 实现显示朋友列表的逻辑
}

void MainWidow::showGroups()
{
    // 实现显示群组列表的逻辑
}

void MainWidow::showAddForm()
{
    AddForm *addForm = new AddForm(); // 创建新的AddForm窗口
    addForm->show(); // 显示新的窗口
}
