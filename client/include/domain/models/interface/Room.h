#ifndef ROOM_H
#define ROOM_H

#include "RoomMember.h"

#include <vector>

class Room {
public:
    virtual int roomId();

    virtual std::vector<RoomMember *> members() = 0;

    virtual RoomMember *host() = 0;
};

#endif // ROOM_H
