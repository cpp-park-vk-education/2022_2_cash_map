#ifndef VIDEOROOM_H
#define VIDEOROOM_H

#include "include/domain/models/interface/RoomMember.h"
#include "include/domain/models/interface/Room.h"

#include <QString>


class VideoRoom : public Room {
public:
    VideoRoom(RoomMember *host, QString roomId);
    ~VideoRoom();
    VideoRoom(VideoRoom &room) = default;
    VideoRoom(VideoRoom &&room);
    VideoRoom &operator=(VideoRoom &room) = default;
    VideoRoom &operator=(VideoRoom &&room);

    virtual std::vector<RoomMember *> members() override;

    virtual RoomMember *host() override;

    virtual QString getRoomId() override;

private:
    RoomMember *hostMember;
    QString roomId;
    std::vector<RoomMember *> membersList;
};


#endif // VIDEOROOM_H
