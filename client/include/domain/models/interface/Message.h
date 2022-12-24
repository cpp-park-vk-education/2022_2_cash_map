#ifndef MESSAGE_H
#define MESSAGE_H

#include "RoomMember.h"

#include <string>

class Message {
public:
    virtual QString messageContent() = 0;

    virtual QString messageTime() = 0;

    virtual QString messageSender() = 0;

};

#endif // MESSAGE_H
