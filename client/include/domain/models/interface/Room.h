#ifndef ROOM_H
#define ROOM_H

#include "RoomMember.h"

#include <QString>
#include <vector>

class Room {
public:
    virtual const QList<RoomMember *> &getMembers() = 0;

    virtual RoomMember *getHost() = 0;

    virtual const QString &getRoomId() = 0;

    virtual const QString &getSource() = 0;

    virtual bool getPlayingState() = 0;

    virtual void setPlayingState(bool state) = 0;

    virtual QString getService() = 0;

    virtual void setService(const QString &) = 0;

    virtual void setSource(const QString &source) = 0;

    virtual void removeMember(RoomMember *member) = 0;

    virtual void addMember(RoomMember *member) = 0;
};

#endif // ROOM_H
