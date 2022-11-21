#include "include/domain/VideoRoomManager.h"


void VideoRoomManager::startWatching() {
    // передаем запрос к webEngine
};
void VideoRoomManager::stopWatching() {
    // передаем запрос к webEngine
}

void VideoRoomManager::changeVideoContent() {
    // передаем запрос к WatchUpServerClient
}

void VideoRoomManager::rewindTo(int timeStamp) {
    // передаем запрос к webEngine
}

void VideoRoomManager::kickMember(RoomMember *) {
    // roomMembers.remove_if(...)
    // emit memeberKicked
}

void VideoRoomManager::acceptNewMember(User *) {
    // roomMembers.push_back(VideoRoomMember(...))
}

int VideoRoomManager::getRoomId() {
    return 0;
}

void VideoRoomManager::sendMessage() {

}
