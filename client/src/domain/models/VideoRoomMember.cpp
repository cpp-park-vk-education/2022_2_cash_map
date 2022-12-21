#include "include/domain/models/VideoRoomMember.h"



VideoRoomMember::VideoRoomMember(const QString &username, const QString &id) : username(username),
                                                                               id(id) {}

QString VideoRoomMember::getUsername() {
    return username;
}

QString VideoRoomMember::getUserId() {
    return id;
}
