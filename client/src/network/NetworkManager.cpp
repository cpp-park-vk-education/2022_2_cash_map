#include "include/network/NetworkManager.h"

#include <QJsonDocument>

NetworkManager* NetworkManager::instance = nullptr;

NetworkManager::NetworkManager(QObject *parent) : QObject(parent),
                                                  client(new WatchUpServerClient()) {

    client->connectToServer();
    qDebug() << "????";
    connect(client, SIGNAL(connected()), this, SIGNAL(sessionStarted()));
    connect(client, SIGNAL(disconnected()), this, SIGNAL(sessionInterrupted()));
    connect(client, SIGNAL(onResponseReceived(const QString &)), this, SLOT(handleResponse(const QString &)));
}


void NetworkManager::sendCreateRoomRequest() {
    QString request = "{\"type\": \"create\"}";
    qDebug() << "sent";
    client->sendRequest(request);
}
void NetworkManager::sendLeaveRoomRequest() {
    QString request = "{\"type\": \"leave\"}";
    client->sendRequest(request);
}
void NetworkManager::sendJoinRoomRequest(const QString &roomID) {
    QString request = "{\"type\": \"join\", \"rood_id\": \"" + roomID + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendPlayRequest() {
    QString request = "{\"type\": \"play\"}";
    client->sendRequest(request);
}

void NetworkManager::sendPauseRequest(int timeStamp) {
    QString stringed = QString(std::to_string(timeStamp).c_str());
    QString request = "{\"type\": \"pause\", \"time\": \"" + stringed + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendContentChangedRequest(const QString &url) {
    QString request = "{\"type\": \"s_src\", \"src\": \"" + url + "\"}";
    client->sendRequest(request);
}

void NetworkManager::sendRewindRequest(int timeStamp) {
    QString stringed = QString(std::to_string(timeStamp).c_str());
    QString request = "{\"type\": \"s_time\", \"time\": \"" + stringed + "\"}";
    client->sendRequest(request);
}

void NetworkManager::handleResponse(const QString &message) {
    // обращаемся к сериалайзеру
    QString json_string;
    QByteArray json_bytes = json_string.toLocal8Bit();
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
    } else if (map["type"] == "play") {
        emit playSignal(map);
    } else if (map["type"] == "pause") {
        emit pauseSignal(map);
    } else if (map["type"] == "s_src") {
        emit contentChangedSignal(map);
    }
}

void NetworkManager::parseResponse() {}

NetworkManager::~NetworkManager() {
    delete client;
}
