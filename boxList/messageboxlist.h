#ifndef MESSAGEBOXLIST_H
#define MESSAGEBOXLIST_H

#include "boxlist.h"
#include "smallWidget/messagebox.h"
#include "manager/usergroupmanager.h"
class MessageBoxList : public BoxList
{
    Q_OBJECT
public:
    explicit MessageBoxList(QWidget *parent = nullptr);
    ~MessageBoxList();
    void addMessageBox(MessageBox *messageBox);
    void deleteMessageBox(QPair<int,QString> index);
    void updataMessageBox(Message message);
    int UID=-1;
private:
    QMap<QPair<int,QString>,MessageBox*> messageBoxMap;

signals:
    void passMessageBox(MessageBox *messageBox);
};

#endif // MESSAGEBOXLIST_H
