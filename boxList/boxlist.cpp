#include "boxlist.h"

#include <QPushButton>
#include <QScrollBar>
BoxList::BoxList(QWidget *parent)
    : QWidget{parent}
{
    /*
      结构：
      this
      └──QVBoxLayout
           └──QScrollArea
                └── QWidget
                    └── QVBoxLayout
                        ├── Widget1
                        └── Widget2
     */
    mainLayout = new QVBoxLayout(this);
    scrollArea = new QScrollArea(this);
    contentWidget = new QWidget(scrollArea);
    layout = new QVBoxLayout(contentWidget);
    this->setLayout(mainLayout);
    mainLayout->addWidget(scrollArea);
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true); // 确保内容窗口可以调整大小以适应 QScrollArea
    contentWidget->setLayout(layout);
    layout->setAlignment(Qt::AlignTop);// 设置布局顶部对齐
    layout->setContentsMargins(2, 2, 2, 2);//设置上下左右边距
    mainLayout->setContentsMargins(0, 0, 0, 0);//设置上下左右边距
    scrollArea->show();
}

void BoxList::addWidget(QWidget *widget)
{
    if (layout->indexOf(widget) == -1)//如果不在则添加
    {
        layout->addWidget(widget);
    }
}

void BoxList::deleteWidget(QWidget *widget)
{
    if (layout->indexOf(widget) != -1)//如果在则移除
    {
        layout->removeWidget(widget);
        delete widget;
    }
}

void BoxList::scrollToBottom()
{
    scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
}
