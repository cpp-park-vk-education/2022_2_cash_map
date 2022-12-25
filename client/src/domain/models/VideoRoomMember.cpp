#include "include/domain/models/VideoRoomMember.h"



VideoRoomMember::VideoRoomMember(const QString &username, const QString &id, const QString &timeStamp) : username(username),
                                                                                                         id(id),
                                                                                                         timeStamp(timeStamp) {}

QString VideoRoomMember::getUsername() {
    return username;
}

QString VideoRoomMember::getUserId() {
    return id;
}


QString VideoRoomMember::getCurrentTimeStamp() {
    return timeStamp;
}

void VideoRoomMember::setTimeStamp(const QString &timeStamp) {
    this->timeStamp = timeStamp;
}
