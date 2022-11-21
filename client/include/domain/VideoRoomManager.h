#ifndef VIDEOROOMMANAGER_H
#define VIDEOROOMMANAGER_H

#include "include/domain/interface/RoomManager.h"



class VideoRoomManager : public RoomManager {
public:
    VideoRoomManager() = default;
    ~VideoRoomManager() = default;

    virtual void startWatching() override;

    virtual void stopWatching() override;

    virtual void changeVideoContent() override;

    virtual void rewindTo(int timeStamp) override;

    virtual void kickMember(RoomMember *) override;

    virtual void acceptNewMember(User *) override;

    virtual int getRoomId() override;

    virtual void sendMessage() override;

private:
    std::vector<RoomMember *> roomMembers;

};


#endif // VIDEOROOMMANAGER_H
