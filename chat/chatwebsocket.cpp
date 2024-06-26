#include "chatwebsocket.h"

ChatWebSocket::ChatWebSocket(QObject *parent)
    : QObject{parent}
{
    webSocket = new QWebSocket();
    connect(webSocket, &QWebSocket::connected, this, &ChatWebSocket::onConnected);
    connect(webSocket, &QWebSocket::disconnected, this, &ChatWebSocket::onDisconnected);
    connect(webSocket, &QWebSocket::textMessageReceived, this, &ChatWebSocket::onTextMessageReceived);
}

ChatWebSocket::~ChatWebSocket()
{
    delete webSocket;
}

void ChatWebSocket::connectToServer(const QUrl &url)
{
    webSocket->open(url);
}

void ChatWebSocket::disconnectFromServer()
{
    webSocket->close();
}

void ChatWebSocket::sendMessage(Message message)
{
    webSocket->sendTextMessage(message.toJsonString());
}

void ChatWebSocket::onConnected()
{
    qDebug()<<"连接成功";
}

void ChatWebSocket::onDisconnected()
{
    qDebug()<<"断开连接";
}

void ChatWebSocket::onTextMessageReceived(const QString &message)
{
    emit textMessageReceived(message);
    //存消息
}
