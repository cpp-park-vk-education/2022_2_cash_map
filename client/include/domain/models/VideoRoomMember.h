#ifndef VIDEOROOMMEMBER_H
#define VIDEOROOMMEMBER_H

#include "include/domain/models/interface/RoomMember.h"
#include <QString>


class VideoRoomMember : public RoomMember {
public:
    VideoRoomMember(const QString &username, const QString &id, const QString &timeStamp);
    ~VideoRoomMember() = default;
    VideoRoomMember(VideoRoomMember &member) = default;
    VideoRoomMember(VideoRoomMember &&member) = default;
    VideoRoomMember &operator=(VideoRoomMember &member) = default;
    VideoRoomMember &operator=(VideoRoomMember &&member) = default;

    virtual QString getUsername() override;

    virtual QString getUserId() override;


    virtual QString getCurrentTimeStamp() override;

    virtual void setTimeStamp(const QString &timeStamp) override;

private:
    QString username;
    QString id;
    QString timeStamp;
};


#endif // VIDEOROOMMEMBER_H
