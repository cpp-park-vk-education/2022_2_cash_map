#ifndef WATCHUPSERVERCLIENT_H
#define WATCHUPSERVERCLIENT_H

#include <QtWebSockets/QtWebSockets>

class WatchUpServerClient : public QObject {

    Q_OBJECT

public:
    explicit WatchUpServerClient(const QUrl &url, QObject *parent = nullptr);

Q_SIGNALS:
    void connectionClosed();

//private Q_SLOTS:
//    void onConnected();
//    void onResponseReceived(QString rawData);

private:
    QWebSocket webSocket;
    QUrl url;

};

#endif // WATCHUPSERVERCLIENT_H
