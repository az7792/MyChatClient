#ifndef BOXLIST_H
#define BOXLIST_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class BoxList : public QWidget
{
    Q_OBJECT
public:
    explicit BoxList(QWidget *parent = nullptr);
    void addWidget(QWidget *widget);
    void deleteWidget(QWidget *widget);
signals:

private:
    QScrollArea *scrollArea;
    QWidget *contentWidget;
    QVBoxLayout *layout;
    QVBoxLayout *mainLayout;
};

#endif // BOXLIST_H
