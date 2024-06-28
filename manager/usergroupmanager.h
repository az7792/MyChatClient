#ifndef USERGROUPMANAGER_H
#define USERGROUPMANAGER_H

#include <QBuffer>
#include <QUrlQuery>
#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>
#include "entity/User.h"
#include "entity/group.h"

class UserGroupManager
{
public:
    UserGroupManager() = delete; // 禁用实例化
    ~UserGroupManager() = default;

    // 定义主机名和端口号常量
    static const QString HOST_NAME;
    static const int PORT;
    static const QString BASE_URL;

    static bool login(QString email, QString password);
    static bool login(int UID, QString password);

    static bool registerUser(QString username, QString email, QString password, QPixmap pixmap);
    static bool updateUserInfo(int UID,QString username, QString email, QPixmap pixmap);
    static bool matchCaptcha(QString email, QString code);
    static bool getCaptchaByEmail(QString email);
    static bool deleteUser(int UID);

    static bool isUserExist(int UID);
    static bool isGroupExist(int groupID);
    static bool isEmailExist(QString email);

    static bool isUsernameValid(QString username);
    static bool isEmailValid(QString email);
    static bool isPasswordValid(QString password);

    static QString encryptPassword(QString password);  // 加密密码

    static bool changeUsername(int UID, QString newUsername);
    static bool changeEmail(int UID, QString newEmail);
    static bool changePassword(QString email, QString newPassword);

    static User getUser(int UID);
    static User getUser(QString email);
    static Group getGroupByGid(int Gid);

    static QVector<User> getContactList(int Uid);
    static QVector<User> getGroupMembers(int Gid);
    static QVector<Group> getGroupList(int Uid);
    static QVector<int> getUidsByUid(int uid);
    static QVector<int> getGidsByUid(int uid);

    friend class AddForm; // 声明 AddForm 为友元类

private:
    static QNetworkAccessManager networkManager;
    static QJsonDocument sendPostRequest(QString endpoint, QUrlQuery postData);
};
#endif // USERGROUPMANAGER_H
