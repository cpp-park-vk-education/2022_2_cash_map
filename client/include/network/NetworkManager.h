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


    void sendCreateRoomRequest(const QString &videoId);
    void sendLeaveRoomRequest();
    void sendJoinRoomRequest(const QString &roomID);
    void sendPlayRequest();
    void sendPauseRequest(QString timeStamp);
    void sendContentChangedRequest(const QString &url);
    void sendRewindRequest(QString timeStamp);
    void sendInvalidRequest();
    void sendAuthRequest(const QString &login, const QString &password);
    void sendRegistrationRequest(const QString &login, const QString &userName, const QString &password);
    void sendLogoutRequest();

    void sendMessageRequest(const QString &content);
public slots:
    void handleResponse(const QString &message);
    void recovery();
signals:
    void sessionStarted();
    void sessionInterrupted();

    void createSignal(const QVariantMap &);
    void leaveSignal(const QVariantMap &);
    void joinSignal(const QVariantMap &);
    void newMemberSignal(const QVariantMap &);
    void playSignal(const QVariantMap &);
    void pauseSignal(const QVariantMap &);
    void contentChangedSignal(const QVariantMap &);
    void rewindSignal(const QVariantMap &);
    void authStatusSignal(const QVariantMap &);
    void registrationStatusSignal(const QVariantMap &);
    void logoutSignal(const QVariantMap &);
    void newMessageSignal(const QVariantMap &);
    void invalid();
private:
    WatchUpServerClient *client;
};

#endif // NETWORKMANAGER_H
