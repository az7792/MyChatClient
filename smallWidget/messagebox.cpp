#include "messagebox.h"
#include "ui_messagebox.h"
MessageBox::MessageBox(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageBox)
{
    ui->setupUi(this);
    this->setBackgroundColor(QColor(255,255,255));
}

MessageBox::~MessageBox()
{
    delete ui;
}

void MessageBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "左键点击";
        //标记为已读
        for(int i=1,len = messages.size();len-i>=0&&i<=numUnread;++i)
        {
            messages[len-i].isRead = 1;
        }
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
void MessageBox::enterEvent(QEnterEvent *event)
{
    this->setBackgroundColor(QColor(245,245,245));
}

//鼠标离开
void MessageBox::leaveEvent(QEvent *event)
{
    this->setBackgroundColor(QColor(255,255,255));
}

void MessageBox::addMessage(Message message)
{
    messages.push_back(message);
    if(message.isRead == 0)
        setNumUnread(this->numUnread + 1);
    else
        setNumUnread(0);//说明当前正在与该对象聊天
    setNewMessage(message.text);
    setTime(message.sentTime);
}

void MessageBox::setTime(const QDateTime &newTime)
{
    time = newTime;
    int hours = newTime.time().hour();
    int minutes = newTime.time().minute();

    // 将小时和分钟格式化为hh:mm
    QString formattedTime = QString("%1:%2")
                                .arg(hours, 2, 10, QChar('0'))   // 保证小时是两位数，不足两位补零
                                .arg(minutes, 2, 10, QChar('0'));
    ui->timeLabel->setText(formattedTime);
}

void MessageBox::setNumUnread(int newNumUnread)
{
    numUnread = newNumUnread;
    if(numUnread==0)
        ui->unReadLabel->setText("");
    else
        ui->unReadLabel->setNum(newNumUnread);
}

void MessageBox::setNewMessage(const QString &newMessage)
{
    this->newMessage = newMessage;
    QString tmpNewMessage;
    if (newMessage.size() > 15)
        tmpNewMessage = newMessage.left(15) + "...";
    else
        tmpNewMessage = newMessage;
    ui->messageLabel->setText(tmpNewMessage);
}

void MessageBox::setName(const QString &newName)
{
    name = newName;
    QString tmpNewName;
    if (name.size() > 10)
        tmpNewName = name.left(10) + "...";
    else
        tmpNewName = name;
    ui->nameLabel->setText(tmpNewName);
}

void MessageBox::setChatType(const QString &newChatType)
{
    chatType = newChatType;
}

void MessageBox::setAvatar(const QPixmap &newAvatar)
{
    avatar = newAvatar;
    ui->avatarLabel->setPixmap(newAvatar);
}

void MessageBox::setId(int newId)
{
    id = newId;
}

void MessageBox::setBackgroundColor(const QColor &backgroundcolor)
{
    QWidget::setStyleSheet(QString("#BGWidget{background-color: %1;}").arg(backgroundcolor.name()));
}
