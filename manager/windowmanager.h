#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include "window/mainwindow.h"
#include "window/userauthwindow.h"
class WindowManager : public QObject
{
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = nullptr);
    ~WindowManager();
    void showUserAuthWindow();
    void showMainWindow(User user);
private:
    UserAuthWindow *userAuthWindow=nullptr;
    MainWindow *mainWindow=nullptr;
signals:
};

#endif // WINDOWMANAGER_H
