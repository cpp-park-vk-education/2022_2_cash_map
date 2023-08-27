#ifndef WATCHUPSERVERCLIENT_H
#define WATCHUPSERVERCLIENT_H

#include <QtWebSockets/QtWebSockets>


class WatchUpServerClient : public QObject {

    Q_OBJECT

public:
    WatchUpServerClient(QObject *parent = nullptr);
    ~WatchUpServerClient();

    void connectToServer();
    QAbstractSocket::SocketState getSocketState();

public slots:
    void logError(QAbstractSocket::SocketError error);
    void sendRequest(const QString &message);
    void close();
signals:
    void disconnected();
    void connected();

    void onResponseReceived(const QString &message);

private:
    QWebSocket *webSocket;
    QUrl url;

};

#endif // WATCHUPSERVERCLIENT_H
