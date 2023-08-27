#ifndef MAINWIDGETMANAGER_H
#define MAINWIDGETMANAGER_H

#include "include/domain/models/interface/Room.h"
#include "include/network/NetworkManager.h"

#include <include/domain/models/interface/RoomMember.h>

class MainWidgetManager : public QObject {
    Q_OBJECT
public:
    MainWidgetManager(QObject *parent = nullptr);
    ~MainWidgetManager() = default;

    Room *createRoomObject(const QVariantMap &response);

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

    void succesfullyOpenedRoom(Room *);
    void succesfullyJoinedRoom(Room *);
    void failedOpeningRoom();
private:
    NetworkManager *networkManager;

};

#endif // MAINWIDGETMANAGER_H
