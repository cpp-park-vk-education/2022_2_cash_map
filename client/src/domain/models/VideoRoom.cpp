#include <include/domain/models/VideoRoom.h>


VideoRoom::VideoRoom(int id, RoomMember *host) : id(id), hostMember(host), membersList() {
    membersList.push_back(host);
};

VideoRoom::VideoRoom(VideoRoom &&room) {
    if (&room != this) {

        id = room.id;
        hostMember = room.hostMember;
        membersList = std::move(room.membersList);
    }
};

VideoRoom &VideoRoom::operator=(VideoRoom &&room) {
    if (&room != this) {

        id = room.id;
        hostMember = room.hostMember;
        membersList = std::move(room.membersList);
    }
    return *this;
};

int VideoRoom::roomId() {
    return id;
}

std::vector<RoomMember *> VideoRoom::members() {
    return membersList;
}

RoomMember *VideoRoom::host() {
    return hostMember;
}
