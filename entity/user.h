#ifndef USER_H
#define USER_H

#include <QPixmap>
#include <QObject>
#include <QString>
#include<QJsonDocument>
#include<QJsonObject>


class User
{
public:
    User(int UID,QString username,QString email,QPixmap avatar);
    User();
    int getUID();
    QString getUsername();
    QString getEmail();
    QPixmap getAvatar();
    void setUID(int UID);
    void setUsername(QString username);
    void setEmail(QString email);
    void setAvatar(QPixmap avatar);

    static User toUser(QJsonObject jsonObject);//json转User
private:
    int UID=-1;
    QString username;
    QString email;
    QPixmap avatar;
};

#endif // USER_H
