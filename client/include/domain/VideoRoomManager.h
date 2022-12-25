#ifndef VIDEOROOMMANAGER_H
#define VIDEOROOMMANAGER_H

#include "include/UI/YoutubeWatcher.h"
#include "include/domain/interface/RoomManager.h"
#include "include/domain/models/interface/Room.h"
#include "include/network/NetworkManager.h"



class VideoRoomManager : public RoomManager {
public:
    VideoRoomManager(Room *room, YoutubeWatcher *watcher);

    ~VideoRoomManager();

    virtual void changeVideoContent(const QString &url) override;

    virtual void reconnect() override;

    virtual void rewindTo(int timeStamp) override;

    virtual void kickMember(RoomMember *) override;

    virtual QString getRoomId() override;

    virtual const QList<RoomMember *> &getMembersList() override;

    virtual void sendMessage() override;

    virtual void updateRoomState() override;

    virtual void leave() override;
public slots:
    virtual void checkRoomState() override;
    virtual void acceptNewMember(const QVariantMap &) override;
    virtual void removeMember(const QVariantMap &) override;
    virtual void changeVideoContent(const QVariantMap &) override;
    virtual void startWatching(const QVariantMap &) override;
    virtual void stopWatching(const QVariantMap &) override;
private:
    QString convertTimeStampToString(int timeStamp);
    int convertTimeStampToInt(QString timeStamp);
    void updatePlayerState();
private:
    PlayerState startState;
    YoutubeWatcher *watcher;
    NetworkManager *networkManager;

    Room *room;
    QTimer timer;
};


#endif // VIDEOROOMMANAGER_H
