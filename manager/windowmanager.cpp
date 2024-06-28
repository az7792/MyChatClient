#include "windowmanager.h"

WindowManager::WindowManager(QObject *parent)
    : QObject{parent}
{
    showUserAuthWindow();
}

WindowManager::~WindowManager()
{
    if (userAuthWindow)
    {
        delete userAuthWindow;
        userAuthWindow = nullptr;
    }

    if (mainWindow)
    {
        delete mainWindow;
        mainWindow = nullptr;
    }
}

void WindowManager::showUserAuthWindow()
{
    if (mainWindow)
    {
        delete mainWindow;
        mainWindow = nullptr;
    }

    userAuthWindow = new UserAuthWindow();
    userAuthWindow->show();
    connect(userAuthWindow,&UserAuthWindow::loggedIn,this,&WindowManager::showMainWindow);
}

void WindowManager::showMainWindow(User user)
{
    if (userAuthWindow)
    {
        delete userAuthWindow;
        userAuthWindow = nullptr;
    }

    mainWindow = new MainWindow();
    mainWindow->setUser(user);
    mainWindow->show();
    connect(mainWindow,&MainWindow::logout,this,&WindowManager::showUserAuthWindow);
}
