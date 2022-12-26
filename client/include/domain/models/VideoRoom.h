#ifndef VIDEOROOM_H
#define VIDEOROOM_H

#include "include/domain/models/interface/RoomMember.h"
#include "include/domain/models/interface/Room.h"

#include <QString>
#include <QList>


class VideoRoom : public Room {
public:
    VideoRoom(RoomMember *host, QString roomId, const QList<RoomMember *> &membersList, const QString &source, const QString &service, bool playingState);
    ~VideoRoom();
    VideoRoom(VideoRoom &room) = default;
    VideoRoom(VideoRoom &&room);
    VideoRoom &operator=(VideoRoom &room) = default;
    VideoRoom &operator=(VideoRoom &&room);

    virtual QString getService() override;

    virtual void setService(const QString &) override;

    virtual const QList<RoomMember *> &getMembers() override;

    virtual const QString &getSource() override;

    virtual void setSource(const QString &source) override;

    virtual bool getPlayingState() override;

    virtual void setPlayingState(bool state) override;

    virtual RoomMember *getHost() override;

    virtual const QString &getRoomId() override;

    virtual void removeMember(RoomMember *member) override;

    virtual void addMember(RoomMember *member) override;

private:
    QString service;
    RoomMember *hostMember;
    QString roomId;
    QString source;
    QList<RoomMember *> membersList;
    bool playingState;
};


#endif // VIDEOROOM_H
