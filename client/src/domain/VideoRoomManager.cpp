#include "include/domain/VideoRoomManager.h"
#include "include/domain/models/VideoRoom.h"
#include "include/domain/models/VideoRoomMember.h"


VideoRoomManager::VideoRoomManager(const QString &username, YoutubeWatcher *watcher) : startState(watcher->getState()),
                                                                                       watcher(watcher),
                                                                                       networkManager(NetworkManager::getInstance()) {
    RoomMember *host = new VideoRoomMember(username);
    room = new VideoRoom(host);

}

void VideoRoomManager::checkRoomState() {
    PlayerState state = watcher->getState();
    if (state.playing != startState.playing && state.playing == false) {
        networkManager->sendPauseRequest(state.timestamp);
    } else if (state.playing != startState.playing && state.playing == true) {
        networkManager->sendPlayRequest();
    } else if (state.speed != startState.speed) {

    }

    startState = state;
}

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


void VideoRoomManager::updateRoomState() {

}
