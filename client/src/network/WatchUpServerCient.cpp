#include "include/network/WatchUpServerClient.h"


WatchUpServerClient::WatchUpServerClient(const QUrl &url, QObject *parent) : QObject(parent), url(url) {}


void WatchUpServerClient::onConnected() {
    webSocket.open(url);
}

void onResponseReceived(QString rawData) {

}
