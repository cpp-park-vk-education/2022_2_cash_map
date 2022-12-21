#include "include/domain/models/VideoRoom.h"


VideoRoom::VideoRoom(RoomMember *host, QString roomId) : hostMember(host), roomId(roomId), membersList() {
    membersList.push_back(host);
};

VideoRoom::VideoRoom(VideoRoom &&room) {
    if (&room != this) {

        hostMember = room.hostMember;
        membersList = std::move(room.membersList);
    }
};

VideoRoom &VideoRoom::operator=(VideoRoom &&room) {
    if (&room != this) {

        hostMember = room.hostMember;
        membersList = std::move(room.membersList);
    }
    return *this;
};


std::vector<RoomMember *> VideoRoom::members() {
    return membersList;
}

RoomMember *VideoRoom::host() {
    return hostMember;
}

QString VideoRoom::getRoomId() {
    return roomId;
}

VideoRoom::~VideoRoom() {
    delete hostMember;
}
