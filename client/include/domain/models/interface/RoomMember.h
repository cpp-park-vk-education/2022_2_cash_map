#ifndef ROOMMEMBER_H
#define ROOMMEMBER_H

#include <string>


class RoomMember {
public:
    virtual std::string username() = 0;

    virtual int currentTimeStamp() = 0;

    virtual bool onPause() = 0;

    virtual bool isHost() = 0;

    virtual void setTimeStamp(int newTimeStamp) = 0;

    virtual void setHostStatus() = 0;

    virtual void setPlaybackStatus(bool status) = 0;
};

#endif // ROOMMEMBER_H
