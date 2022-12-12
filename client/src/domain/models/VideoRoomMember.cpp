#include "include/domain/models/VideoRoomMember.h"



VideoRoomMember::VideoRoomMember(const QString &username) : username(username) {}

QString VideoRoomMember::getUsername() {
    return username;
}
