#ifndef VIDEOROOMMANAGER_H
#define VIDEOROOMMANAGER_H

#include "include/UI/YoutubeWatcher.h"
#include "include/domain/interface/RoomManager.h"
#include "include/domain/models/interface/Room.h"
#include "include/network/NetworkManager.h"



class VideoRoomManager : public RoomManager {
public:
    VideoRoomManager(const QString &username, YoutubeWatcher *watcher);
    ~VideoRoomManager() = default;

    virtual void startWatching() override;

    virtual void stopWatching() override;

    virtual void changeVideoContent() override;

    virtual void rewindTo(int timeStamp) override;

    virtual void kickMember(RoomMember *) override;

    virtual void acceptNewMember(User *) override;

    virtual int getRoomId() override;

    virtual void sendMessage() override;

    virtual void updateRoomState() override;
public slots:
    virtual void checkRoomState() override;

private:
    PlayerState startState;
    YoutubeWatcher *watcher;
    NetworkManager *networkManager;
    std::vector<RoomMember *> roomMembers;
    Room *room;

};


#endif // VIDEOROOMMANAGER_H
