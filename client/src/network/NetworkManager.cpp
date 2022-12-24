#include "include/network/NetworkManager.h"

#include <QJsonDocument>

NetworkManager* NetworkManager::instance = nullptr;

NetworkManager::NetworkManager(QObject *parent) : QObject(parent),
                                                  client(new WatchUpServerClient()) {

    client->connectToServer();
    connect(client, SIGNAL(connected()), this, SIGNAL(sessionStarted()));
    connect(client, SIGNAL(disconnected()), this, SIGNAL(sessionInterrupted()));
    connect(client, SIGNAL(onResponseReceived(const QString &)), this, SLOT(handleResponse(const QString &)));
}


void NetworkManager::sendCreateRoomRequest(const QString &videoId) {
    QString request = "{\"type\": \"create\", \"src\": \"" + videoId + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendLeaveRoomRequest() {
    QString request = "{\"type\": \"leave\"}";
    client->sendRequest(request);
}

void NetworkManager::sendJoinRoomRequest(const QString &roomID) {
    QString request = "{\"type\": \"join\", \"room_id\": \"" + roomID + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendPlayRequest() {
    QString request = "{\"type\": \"play\"}";
    client->sendRequest(request);
}

void NetworkManager::sendPauseRequest(QString timeStamp) {
    QString request = "{\"type\": \"pause\", \"time\": \"" + timeStamp + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendContentChangedRequest(const QString &url) {
    QString request = "{\"type\": \"s_src\", \"src\": \"" + url + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendRewindRequest(QString timeStamp) {
    QString request = "{\"type\": \"s_time\", \"time\": \"" + timeStamp + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendAuthRequest(const QString &login, const QString &password) {
    QString request = "{\"type\": \"login\", \"login\": \"" + login + "\", \"password\": \"" + password + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendRegistrationRequest(const QString &login, const QString &userName, const QString &password) {
    QString request = "{\"type\": \"reg\", \"login\": \"" + login + "\", \"nick\": \"" + userName + "\", \"password\": \"" + password + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendLogoutRequest() {
    QString request = "{\"type\": \"logout\"}";
    client->sendRequest(request);
}

void NetworkManager::sendMessageRequest(const QString &content) {
    QString request = "{\"type\": \"chat\", \"msg\": \"" + content + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendInvalidRequest() {
    QString request = "{\"type\": \"invalid\"}";
    client->sendRequest(request);
}

void NetworkManager::handleResponse(const QString &message) {
    // обращаемся к сериалайзеру
    QByteArray json_bytes = message.toUtf8();
    auto json_doc = QJsonDocument::fromJson(json_bytes);

    QJsonObject obj = json_doc.object();
    qDebug() << "[LOGGER] " << message << '\n';
    QVariantMap map = obj.toVariantMap();
    if (map["type"] == "create") {
        emit createSignal(map);
    } else if (map["type"] == "leave"){
        emit leaveSignal(map);
    } else if (map["type"] == "join") {
        emit joinSignal(map);
    } else if (map["type"] == "incomer") {
        emit newMemberSignal(map);
    }else if (map["type"] == "play") {
        emit playSignal(map);
    } else if (map["type"] == "pause") {
        emit pauseSignal(map);
    } else if (map["type"] == "s_src") {
        emit contentChangedSignal(map);
    } else if (map["type"] == "login") {
        emit authStatusSignal(map);
    } else if (map["type"] == "reg") {
        emit registrationStatusSignal(map);
    } else if (map["type"] == "logout") {
        qDebug() << "LOGOUT";
        emit logoutSignal(map);
    } else if (map["type"] == "s_time") {
        emit rewindSignal(map);
    } else if (map["type"] == "chat") {
        emit newMessageSignal(map);
    } else if (map["type"] == "invalid") {
        emit invalid();
    }
}

void NetworkManager::recovery() {
    qDebug() << client->getSocketState();
    client->connectToServer();
}

NetworkManager::~NetworkManager() {
    delete client;
}
