#include "usergroupmanager.h"


const QString UserGroupManager::HOST_NAME = "localhost";
const int UserGroupManager::PORT = 8080;
const QString UserGroupManager::BASE_URL = "http://" + UserGroupManager::HOST_NAME + ":" + QString::number(UserGroupManager::PORT) + "/";
QNetworkAccessManager UserGroupManager::networkManager;


// 发POST请求,传入接口地址和数据，返回jsonDocument
QJsonDocument UserGroupManager::sendPostRequest(QString endpoint, QUrlQuery postData)
{
    QNetworkRequest request(QUrl(BASE_URL + endpoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // 发送POST请求
    QNetworkReply *reply = networkManager.post(request, postData.toString(QUrl::FullyEncoded).toUtf8());

    // 等待请求完成
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // 解析响应
    QJsonDocument jsonDocument;
    if (reply->isFinished() && reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        jsonDocument = QJsonDocument::fromJson(responseData);
    }
    else
    {
        qDebug() << "Error: " << reply->errorString();
    }
    reply->deleteLater();
    return jsonDocument;
}


// 登录请求ByEmail
bool UserGroupManager::login(QString email, QString password)
{
    if (!isEmailValid(email))
        return false;
    if (!isPasswordValid(password))
        return false;
    password = encryptPassword(password);

    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("email", email);
    postData.addQueryItem("password", password);

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("login/email", postData);

    // 解析响应
    bool success = false;
    if (!jsonDocument.isEmpty())
    {
        success = jsonDocument.object()["success"].toBool();
    }
    return success;
}

// 登录请求ByUID
bool UserGroupManager::login(int UID, QString password)
{
    if (UID <= 0)
        return false;
    if (!isPasswordValid(password))
        return false;
    password = encryptPassword(password);

    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("uid", QString::number(UID));
    postData.addQueryItem("password", password);

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("login/uid", postData);

    // 解析响应
    bool success = false;
    if (!jsonDocument.isEmpty())
    {
        success = jsonDocument.object()["success"].toBool();
    }
    return success;
}

// 注册请求
bool UserGroupManager::registerUser(QString username, QString email, QString password, QPixmap pixmap)
{
    // 验证数据格式
    if (isUsernameValid(username) == false)
        return false;
    if (isEmailValid(email) == false)
        return false;
    if (isPasswordValid(password) == false)
        return false;

    // 验证用户是否存在
    if (isEmailExist(email) == true)
        return false;
    password = encryptPassword(password);

    // pixmap转base64
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "JPG"); // 保存为 JPG 格式
    buffer.close();
    QString base64String = byteArray.toBase64();
    base64String = QUrl::toPercentEncoding(base64String);
    // 注册请求
    //  构造参数
    QUrlQuery postData;
    postData.addQueryItem("username", username);
    postData.addQueryItem("email", email);
    postData.addQueryItem("password", password);
    postData.addQueryItem("avatar", base64String);

    QJsonDocument jsonDocument = sendPostRequest("register", postData);

    // 解析响应
    bool success = false;
    if (!jsonDocument.isEmpty())
    {
        success = jsonDocument.object()["success"].toBool();
    }
    return success;
}

// 匹配验证码
bool UserGroupManager::matchCaptcha(QString email, QString code)
{
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("email", email);
    postData.addQueryItem("code", code);

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("matchCaptcha", postData);

    // 解析响应
    bool success = false;
    if (!jsonDocument.isEmpty())
    {
        success = jsonDocument.object()["success"].toBool();
    }
    return success;
}

// 通过邮箱获取验证码
bool UserGroupManager::getCaptchaByEmail(QString email)
{
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("email", email);

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("sendCaptchaByEmail", postData);

    // 解析响应
    bool success = false;
    if (!jsonDocument.isEmpty())
    {
        success = jsonDocument.object()["success"].toBool();
    }
    return success;
}

// 注销用户
bool UserGroupManager::deleteUser(int UID)
{
}
// 用户是否存在
bool UserGroupManager::isUserExist(int UID)
{
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("uid",QString::number(UID));

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("exists/uid", postData);

    // 读取响应数据
    return jsonDocument.object()["exist"].toBool();
}

bool UserGroupManager::isGroupExist(int groupID)
{
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("groupid",QString::number(groupID));

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("exists/groupid", postData);

    // 读取响应数据
    return jsonDocument.object()["exist"].toBool();
}

// 邮箱是否存在
bool UserGroupManager::isEmailExist(QString email)
{
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("email",email);

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("exists/email", postData);

    // 读取响应数据
    return jsonDocument.object()["exist"].toBool();
}

// 用户名是否合法
bool UserGroupManager::isUsernameValid(QString username)
{
    // 使用正则表达式匹配用户名格式
    static const QRegularExpression usernameRegex(R"(^[a-zA-Z0-9一-龥_]{1,20}$)"); // 由 1 到 20 个汉字、字母、数字或下划线组成
    QRegularExpressionMatch match = usernameRegex.match(username);
    return match.hasMatch();
}

// 邮箱是否合法
bool UserGroupManager::isEmailValid(QString email)
{
    // 使用正则表达式匹配邮箱格式
    static const QRegularExpression emailRegex(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    QRegularExpressionMatch match = emailRegex.match(email);
    return (match.hasMatch() && email.size() <= 100);
}

// 密码是否合法
bool UserGroupManager::isPasswordValid(QString password)
{
    if (password.size() < 6 || password.size() > 20)
        return false;

    int isupper = 0, islower = 0, isdigit = 0, isspecial = 0;

    for (const QChar &ch : password)
    {
        if (ch.isUpper()) // 大写字母
            isupper = 1;
        else if (ch.isLower()) // 小写字母
            islower = 1;
        else if (ch.isDigit()) // 数字
            isdigit = 1;
        else if (ch.isPunct() || ch.isSymbol()) // 标点符号或符号字符
            isspecial = 1;
    }
    // 至少包含两种类型的符号
    return isupper + islower + isdigit + isspecial >= 2;
}

// 加密密码
QString UserGroupManager::encryptPassword(QString password)
{
    QByteArray byteArray = password.toUtf8();
    // SHA-256加密
    QCryptographicHash hash(QCryptographicHash::Sha256);
    hash.addData(byteArray);
    QByteArray hashedData = hash.result();
    // 转16进制
    return hashedData.toHex();
}

// 修改用户名
bool UserGroupManager::changeUsername(int UID, QString newUsername)
{
}

// 修改邮箱
bool UserGroupManager::changeEmail(int UID, QString newEmail)
{
}

// 修改密码
bool UserGroupManager::changePassword(QString email, QString newPassword)
{
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("email", email);
    postData.addQueryItem("password", encryptPassword(newPassword));

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("updatePassword", postData);

    // 解析响应
    bool success = false;
    if (!jsonDocument.isEmpty())
    {
        success = jsonDocument.object()["success"].toBool();
    }
    return success;
}

// 获取用户信息
User UserGroupManager::getUser(int UID)
{
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("uid", QString::number(UID));

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("getUser/uid", postData);

    // 解析响应
    if (jsonDocument.isEmpty())
        return User();
    QJsonObject jsonObject = jsonDocument.object();
    return User::toUser(jsonObject);
}

// 获取用户信息
User UserGroupManager::getUser(QString email)
{
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("email", email);

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("getUser/email", postData);

    // 解析响应
    if (jsonDocument.isEmpty())
        return User();
    QJsonObject jsonObject = jsonDocument.object();
    return User::toUser(jsonObject);
}

// 获取用户的好友列表
QVector<User> UserGroupManager::getContactList(int Uid)
{
    QVector<User> list;
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("uid", QString::number(Uid));

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("/selectcontact/uid", postData);
    QJsonArray userArray = jsonDocument.array();
    for (const QJsonValue &userValue : userArray)
    {
        QJsonObject userObject = userValue.toObject();
        list.push_back(User::toUser(userObject));
    }
    return list;
}

// 获取用户所有群
QVector<Group> UserGroupManager::getGroupList(int Uid)
{
    QVector<Group> list;
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("uid", QString::number(Uid));

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("getgroups/uid", postData);
    QJsonArray groupArray = jsonDocument.array();
    for (const QJsonValue &groupValue : groupArray)
    {
        QJsonObject groupObject = groupValue.toObject();
        list.push_back(Group::toGroup(groupObject));
    }
    return list;
}

// 根据群id获取用户
QVector<User> UserGroupManager::getGroupMembers(int Gid)
{
    QVector<User> list;
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("groupid", QString::number(Gid));

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("getgroupmembers/user", postData);
    QJsonArray userArray = jsonDocument.array();
    for (const QJsonValue &userValue : userArray)
    {
        QJsonObject userObject = userValue.toObject();
        list.push_back(User::toUser(userObject));
    }
    return list;
}

// 根据群id获取群
Group UserGroupManager::getGroupByGid(int Gid)
{
    Group group;
    // 构造参数
    QUrlQuery postData;
    postData.addQueryItem("groupid", QString::number(Gid));

    // 发送POST请求
    QJsonDocument jsonDocument = sendPostRequest("selectgroup/uid", postData);
    // 解析响应
    if (jsonDocument.isEmpty())
        return Group();
    QJsonObject jsonObject = jsonDocument.object();
    return Group::toGroup(jsonObject);
}
