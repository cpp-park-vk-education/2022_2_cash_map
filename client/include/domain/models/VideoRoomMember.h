#ifndef VIDEOROOMMEMBER_H
#define VIDEOROOMMEMBER_H

#include "include/domain/models/interface/RoomMember.h"
#include "include/domain/models/interface/User.h"


class VideoRoomMember : public RoomMember {
public:
    VideoRoomMember(User *user, int timeStamp, bool isHost, bool playbackStatus);
    ~VideoRoomMember() = default;
    VideoRoomMember(VideoRoomMember &member) = default;
    VideoRoomMember(VideoRoomMember &&member) = default;
    VideoRoomMember &operator=(VideoRoomMember &member) = default;
    VideoRoomMember &operator=(VideoRoomMember &&member) = default;

    virtual std::string username() override;

    virtual int currentTimeStamp() override;

    virtual bool onPause() override;

    virtual bool isHost() override;

    virtual void setTimeStamp(int newTimeStamp) override;

    virtual void setHostStatus() override;

    virtual void setPlaybackStatus(bool status) override;

private:
    User *user;
    int timeStamp;
    bool hostStatus;
    bool playbackStatus;
};


#endif // VIDEOROOMMEMBER_H
