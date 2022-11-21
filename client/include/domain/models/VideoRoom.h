#ifndef VIDEOROOM_H
#define VIDEOROOM_H

#include "include/domain/models/interface/RoomMember.h"
#include "include/domain/models/interface/Room.h"


class VideoRoom : public Room {
public:
    VideoRoom(int id, RoomMember *host);
    ~VideoRoom() = default;
    VideoRoom(VideoRoom &room) = default;
    VideoRoom(VideoRoom &&room);
    VideoRoom &operator=(VideoRoom &room) = default;
    VideoRoom &operator=(VideoRoom &&room);

    virtual int roomId() override;

    virtual std::vector<RoomMember *> members() override;

    virtual RoomMember *host() override;

private:
    int id;
    RoomMember *hostMember;
    std::vector<RoomMember *> membersList;
};


#endif // VIDEOROOM_H
