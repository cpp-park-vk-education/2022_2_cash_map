#ifndef ROOM_H
#define ROOM_H

#include "RoomMember.h"

#include <QString>
#include <vector>

class Room {
public:
    virtual std::vector<RoomMember *> members() = 0;

    virtual RoomMember *host() = 0;

    virtual QString getRoomId() = 0;
};

#endif // ROOM_H
