#include "include/network/WatchUpServerClient.h"


WatchUpServerClient::WatchUpServerClient(QObject *parent) : QObject(parent) {
    url = QUrl("wss://2835-46-242-13-178.eu.ngrok.io");
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
    qDebug() << "777";
    webSocket->open(url);
}

void WatchUpServerClient::close() {
    webSocket->close();
}

void WatchUpServerClient::sendRequest(const QString &message) {
    webSocket->sendTextMessage(message);
}

WatchUpServerClient::~WatchUpServerClient() {
    delete webSocket;
}
