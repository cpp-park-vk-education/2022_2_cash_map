#include "include/domain/models/VideoRoomMember.h"
#include "include/domain/models/interface/User.h"


VideoRoomMember::VideoRoomMember(User *user, int timeStamp, bool isHost, bool playbackStatus) : user(user),
                                                                               timeStamp(timeStamp),
                                                                               hostStatus(isHost),
                                                                               playbackStatus(playbackStatus) {};

std::string VideoRoomMember::username() {
    return user->userName();
}

int VideoRoomMember::currentTimeStamp() {
    return timeStamp;
}

bool VideoRoomMember::onPause() {
    return playbackStatus;
}

bool VideoRoomMember::isHost() {
    return hostStatus;
}

void VideoRoomMember::setTimeStamp(int newTimeStamp) {
    timeStamp = newTimeStamp;
}

void VideoRoomMember::setHostStatus() {
    hostStatus = true;
}

void VideoRoomMember::setPlaybackStatus(bool status) {
    hostStatus = status;
}
