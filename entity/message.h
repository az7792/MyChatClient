#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class Message{
public:
    Message();
    Message(int form,int to,QString receiverType,QString text,QString type);
    Message(int messageId,int form,int to,QString receiverType,QString text,QString type,QDateTime sentTime);
    ~Message();
    int messageId;
    int fromUserUid;
    int toReceiver;
    QString receiverType;
    QString text;
    QString type;
    QDateTime sentTime;
    int isRead = 0;

    QString toJsonString();

    static Message toMessage(QString jsonString);
signals:
};

#endif // MESSAGE_H
