#include "include/domain/models/VideoRoom.h"


VideoRoom::VideoRoom(RoomMember *host, QString roomId,
                     const QList<RoomMember *> &membersList, const QString &source, const QString &service, bool playingState) : service(service),
                                                                                                                                  hostMember(host),
                                                                                                                                  roomId(roomId),
                                                                                                                                  source(source),
                                                                                                                                  membersList(membersList),
                                                                                                                                  playingState(playingState) {
    this->membersList.push_back(host);
}

VideoRoom::VideoRoom(VideoRoom &&room) {
    if (&room != this) {

        hostMember = room.hostMember;
        membersList = std::move(room.membersList);
    }
}

VideoRoom &VideoRoom::operator=(VideoRoom &&room) {
    if (&room != this) {

        hostMember = room.hostMember;
        membersList = std::move(room.membersList);
    }
    return *this;
}

const QList<RoomMember *> &VideoRoom::getMembers() {
    return membersList;
}

void VideoRoom::removeMember(RoomMember *member) {
    membersList.removeAll(member);
}

void VideoRoom::addMember(RoomMember *member) {
    membersList.append(member);
}

RoomMember *VideoRoom::getHost() {
    return hostMember;
}

const QString &VideoRoom::getRoomId() {
    return roomId;
}

const QString &VideoRoom::getSource() {
    return source;
}

void VideoRoom::setSource(const QString &source) {
    this->source = source;
}
bool VideoRoom::getPlayingState() {
    return playingState;
}

void VideoRoom::setPlayingState(bool state) {
    playingState = state;
}

QString VideoRoom::getService() {
    return service;
}

void VideoRoom::setService(const QString &service) {
    this->service = service;
}

VideoRoom::~VideoRoom() {
    delete hostMember;
}
