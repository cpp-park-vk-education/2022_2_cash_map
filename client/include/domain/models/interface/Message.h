#ifndef MESSAGE_H
#define MESSAGE_H

#include "RoomMember.h"

#include <string>

class Message {
public:
    virtual std::string messageContent() = 0;

    virtual int messageTime() = 0;

    virtual RoomMember *messageSender() = 0;

};

#endif // MESSAGE_H
