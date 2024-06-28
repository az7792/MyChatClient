#include "friendbox.h"
#include "ui_friendbox.h"

FriendBox::FriendBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FriendBox)
{
    ui->setupUi(this);
}

FriendBox::FriendBox(User user, QWidget *parent)
    :QWidget(parent),
    ui(new Ui::FriendBox)
{
    ui->setupUi(this);
    setName(user.getUsername());
    setAvatar(user.getAvatar());
    setId(user.getUID());
    setChatType("user");
}

FriendBox::FriendBox(Group group, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendBox)
{
    ui->setupUi(this);
    setName(group.getGroupname());
    setAvatar(group.getAvatar());
    setId(group.getGroupid());
    setChatType("group");
}

FriendBox::~FriendBox()
{
    delete ui;
}

void FriendBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked(this);
    }
    else if (event->button() == Qt::RightButton)
    {
        qDebug() << "右键点击";
    }
    // 调用基类的 mousePressEvent 以确保默认处理
    QWidget::mousePressEvent(event);
}

//鼠标进入
void FriendBox::enterEvent(QEnterEvent *event)
{
    this->setBackgroundColor(QColor(245,245,245));
}

//鼠标离开
void FriendBox::leaveEvent(QEvent *event)
{
    this->setBackgroundColor(QColor(255,255,255));
}

void FriendBox::setName(const QString &newName)
{
    name = newName;
    ui->nameLabel->setText(name);
}

void FriendBox::setChatType(const QString &newChatType)
{
    chatType = newChatType;
}

void FriendBox::setAvatar(const QPixmap &newAvatar)
{
    avatar = newAvatar;
    ui->avatarLabel->setPixmap(avatar);
}

void FriendBox::setId(int newId)
{
    id = newId;
    ui->UIDLabel->setNum(id);
}

void FriendBox::setBackgroundColor(const QColor& backgroundcolor)
{
    QWidget::setStyleSheet(QString("#BGWidget{background-color: %1;}").arg(backgroundcolor.name()));
}
