#ifndef CHATWEBSOCKET_H
#define CHATWEBSOCKET_H

#include <QObject>
#include <QWebSocket>
#include "entity/message.h"
#include <QJsonDocument>
#include <QJsonObject>
class ChatWebSocket : public QObject
{
    Q_OBJECT
public:
    static ChatWebSocket& getInstance() {//获取单例
        static ChatWebSocket instance;
        return instance;
    }
    void connectToServer(const QUrl &url);//连接webSocket服务器
    void disconnectFromServer();//断开连接
    void sendMessage(Message message);//发送消息
signals:
    void textMessageReceived(const QString &message);//将收到的消息以信号的形式发出
public slots:
    void onConnected();//连接成功时触发
    void onDisconnected();//断开时触发
    void onTextMessageReceived(const QString &message);//收到消息时触发
private:
    explicit ChatWebSocket(QObject *parent = nullptr);
    ~ChatWebSocket();
    QWebSocket *webSocket=nullptr;

    // 禁用拷贝构造和赋值运算符
    ChatWebSocket(const ChatWebSocket&) = delete;
    ChatWebSocket& operator=(const ChatWebSocket&) = delete;
};

#endif // CHATWEBSOCKET_H
