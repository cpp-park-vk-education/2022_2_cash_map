#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "include/network/WatchUpServerClient.h"
#include <QObject>


class NetworkManager : public QObject {
    Q_OBJECT
private:
    static NetworkManager *instance;
    NetworkManager(QObject *parent = nullptr);
    NetworkManager(const NetworkManager &) = delete;
    NetworkManager(NetworkManager &&) = delete;
    NetworkManager &operator=(const NetworkManager &) = delete;
    NetworkManager &operator=(NetworkManager &&) = delete;
public:
    static NetworkManager *getInstance() {
        if (!instance) {
            instance = new NetworkManager();
        }
        return instance;
    }
    ~NetworkManager();

    void sendCreateRoomRequest();
    void sendLeaveRoomRequest();
    void sendJoinRoomRequest(const QString &roomID);
    void sendPlayRequest();
    void sendPauseRequest(int timeStamp);
    void sendContentChangedRequest(const QString &url);
    void sendRewindRequest(int timeStamp);

    void parseResponse();
public slots:
    void handleResponse(const QString &message);
signals:
    void sessionStarted();
    void sessionInterrupted();

    void createSignal(const QVariantMap &);
    void leaveSignal(const QVariantMap &);
    void joinSignal(const QVariantMap &);
    void playSignal(const QVariantMap &);
    void pauseSignal(const QVariantMap &);
    void contentChangedSignal(const QVariantMap &);
    void rewindSignal(const QVariantMap &);
private:
    WatchUpServerClient *client;
};

#endif // NETWORKMANAGER_H
