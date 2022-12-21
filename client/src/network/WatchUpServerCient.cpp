#include "include/network/WatchUpServerClient.h"


WatchUpServerClient::WatchUpServerClient(QObject *parent) : QObject(parent) {
    url = QUrl("wss://f8dc-46-242-13-195.eu.ngrok.io");
    webSocket = new QWebSocket();

    connect(webSocket, SIGNAL(connected()), this, SIGNAL(connected()));
    connect(webSocket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));

    connect(webSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(logError(QAbstractSocket::SocketError)));

    connect(webSocket, SIGNAL(textMessageReceived(const QString &)), this, SIGNAL(onResponseReceived(const QString &)));
}

void WatchUpServerClient::logError(QAbstractSocket::SocketError error) {
    qDebug() << error;
    emit disconnected();
}

void WatchUpServerClient::connectToServer() {
    webSocket->open(url);
}

void WatchUpServerClient::close() {
    webSocket->close();
}

void WatchUpServerClient::sendRequest(const QString &message) {
    webSocket->sendTextMessage(message);
}

QAbstractSocket::SocketState WatchUpServerClient::getSocketState() {
    qDebug() << webSocket->state();
    return webSocket->state();
}

WatchUpServerClient::~WatchUpServerClient() {
    delete webSocket;
}
