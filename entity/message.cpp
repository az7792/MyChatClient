#include "message.h"

Message::Message()
{}

Message::Message(int fromUserUid, int toReceiver,QString receiverType,
                 QString text, QString type)
    :fromUserUid(fromUserUid),
    toReceiver(toReceiver),
    receiverType(receiverType),
    text(text),
    type(type)
{
}

Message::Message(int messageId, int fromUserUid, int toReceiver,QString receiverType,
                 QString text, QString type, QDateTime sentTime)
    :messageId(messageId),
    fromUserUid(fromUserUid),
    toReceiver(toReceiver),
    receiverType(receiverType),
    text(text),
    type(type),
    sentTime(sentTime)
{
}

Message::~Message()
{

}

//转JSON
QString Message::toJsonString()
{
    QJsonObject jsonObj;
    jsonObj["fromUserUid"] = fromUserUid;
    jsonObj["toReceiver"] = toReceiver;
    jsonObj["receiverType"] = receiverType;
    jsonObj["text"] = text;
    jsonObj["type"] = type;

    QJsonDocument jsonDoc(jsonObj);
    return QString::fromUtf8(jsonDoc.toJson(QJsonDocument::Compact));
}

//JSON转Message
Message Message::toMessage(QString jsonString)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    int messageId = jsonObj["messageId"].toInt();
    int fromUserUid = jsonObj["fromUserUid"].toInt();
    int toReceiver = jsonObj["toReceiver"].toInt();
    QString receiverType = jsonObj["receiverType"].toString();
    QString text = jsonObj["text"].toString();
    QString type = jsonObj["type"].toString();

    QJsonArray sentTimeArray = jsonObj["sentTime"].toArray();
    QDateTime sentTime(QDate(sentTimeArray[0].toInt(), sentTimeArray[1].toInt(), sentTimeArray[2].toInt()),
                       QTime(sentTimeArray[3].toInt(), sentTimeArray[4].toInt(), sentTimeArray[5].toInt()));

    return Message(messageId, fromUserUid, toReceiver, receiverType, text, type, sentTime);
}

