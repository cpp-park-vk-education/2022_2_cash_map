#include "include/domain/models/VideoRoom.h"


VideoRoom::VideoRoom(RoomMember *host) : hostMember(host), membersList() {
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
