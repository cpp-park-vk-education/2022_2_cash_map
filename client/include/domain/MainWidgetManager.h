#ifndef MAINWIDGETMANAGER_H
#define MAINWIDGETMANAGER_H

#include "include/network/NetworkManager.h"

#include <include/domain/models/interface/RoomMember.h>

class MainWidgetManager : public QObject {
    Q_OBJECT
public:
    MainWidgetManager(QObject *parent = nullptr);
    ~MainWidgetManager() = default;

public slots:
    void createRoom(const QString &videoId);
    void joinRoom(const QString &roomId);
    void leaveRoom();
    void playVideo();

    void manageResponse(const QVariantMap &response);
signals:
    void roomReady();
    void joinReady();
    void leaveDone();
    void playDone();

    void succesfullyOpenedRoom(const QString &roomId);
    void succesfullyJoinedRoom(const QList<RoomMember *> members);
    void failedOpeningRoom();
private:
    NetworkManager *networkManager;

};

#endif // MAINWIDGETMANAGER_H
