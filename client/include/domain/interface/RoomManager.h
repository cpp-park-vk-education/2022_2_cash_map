#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include "include/domain/models/interface/RoomMember.h"
#include "include/domain/models/interface/User.h"

#include <QObject>


class RoomManager : public QObject {
    Q_OBJECT
public:

    virtual void startWatching() = 0;

    virtual void stopWatching() = 0;

    virtual void changeVideoContent() = 0;

    virtual void rewindTo(int timeStamp) = 0;

    virtual void kickMember(RoomMember *) = 0;

    virtual void acceptNewMember(User *) = 0;

    virtual int getRoomId() = 0;

    virtual void sendMessage() = 0;
signals:
    void memberKicked(std::string username);

};

#endif // ROOMMANAGER_H
