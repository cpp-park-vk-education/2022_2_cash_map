#ifndef VIDEOROOMMEMBER_H
#define VIDEOROOMMEMBER_H

#include "include/domain/models/interface/RoomMember.h"
#include <QString>


class VideoRoomMember : public RoomMember {
public:
    VideoRoomMember(const QString &username);
    ~VideoRoomMember() = default;
    VideoRoomMember(VideoRoomMember &member) = default;
    VideoRoomMember(VideoRoomMember &&member) = default;
    VideoRoomMember &operator=(VideoRoomMember &member) = default;
    VideoRoomMember &operator=(VideoRoomMember &&member) = default;

    virtual QString getUsername() override;

private:
    QString username;
};


#endif // VIDEOROOMMEMBER_H
