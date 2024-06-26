#include "sendbox.h"
#include "ui_sendbox.h"

SendBox::SendBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendBox)
{
    ui->setupUi(this);
    ui->messageLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);//设置可选中
    ui->messageLabel->setWordWrap(true);//设置自动换行
    ui->imgLabel->setScaledContents(true);//图片自动适应标签大小
    setStyleSheet("#messageLabel { padding: 12px; }");
}

SendBox::~SendBox()
{
    delete ui;
}

//设置字体颜色
void SendBox::setTextColor(const QColor &textcolor)
{
    setStyleSheet(QString("#messageLabel {color: %1;}").arg(textcolor.name()));
}

//设置背景颜色
void SendBox::setBackgroundColor(const QColor &backgroundcolor)
{
    setStyleSheet(QString("#messageLabel{background-color: %1;}").arg(backgroundcolor.name()));
}

//这是圆角矩形半径
void SendBox::setBordetRadius(const int radius)
{
    setStyleSheet(QString("#messageLabel{border-radius: %1;}").arg(QString::number(radius)));
}

//增加其他样式
void SendBox::setStyleSheet(const QString &style)
{
    QWidget::setStyleSheet(styleSheet()+style);
}

//设置头像图片
void SendBox::setAvatar(const QPixmap &avtar)
{

    QRegion region(ui->imgLabel->rect(), QRegion::Ellipse);
    ui->imgLabel->setMask(region);
    ui->imgLabel->setPixmap(avtar);
}

//设置文本
void SendBox::setText(const QString &text)
{
    ui->messageLabel->setText(text);
}
