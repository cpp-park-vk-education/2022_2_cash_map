#include "include/domain/VideoRoomManager.h"
#include "include/domain/models/VideoRoomMember.h"


VideoRoomManager::VideoRoomManager(const QString &username, const QString &userId, YoutubeWatcher *watcher,
                                   const QString &roomId, QList<RoomMember *> members) : startState(watcher->getState()),
                                                                                               roomId(roomId),
                                                                                               members(members),
                                                                                               watcher(watcher),
                                                                                               networkManager(NetworkManager::getInstance()) {

    this->members.append(new VideoRoomMember(username, userId));
    connect(networkManager, SIGNAL(newMemberSignal(const QVariantMap &)), this, SLOT(acceptNewMember(const QVariantMap &)));
    connect(networkManager, SIGNAL(leaveSignal(const QVariantMap &)), this, SLOT(removeMember(const QVariantMap &)));
    connect(networkManager, SIGNAL(contentChangedSignal(const QVariantMap &)), this, SLOT(changeVideoContent(const QVariantMap &)));
    connect(networkManager, SIGNAL(playSignal(const QVariantMap &)), this, SLOT(startWatching(const QVariantMap &)));
    connect(networkManager, SIGNAL(pauseSignal(const QVariantMap &)), this, SLOT(stopWatching(const QVariantMap &)));
}

void VideoRoomManager::checkRoomState() {
    PlayerState state = watcher->getState();
    if (state.playing != startState.playing && state.playing == true) {
        networkManager->sendPauseRequest(state.timestamp);
    } else if (state.playing != startState.playing && state.playing == false) {
        networkManager->sendPlayRequest();
    } else if (state.speed != startState.speed) {

    }

    startState = state;
}

void VideoRoomManager::leave() {
    networkManager->sendLeaveRoomRequest();

}

void VideoRoomManager::removeMember(const QVariantMap &newMemberInfo) {
    for (auto viewerInfo : newMemberInfo["viewers"].toList()) {
        QString id = viewerInfo.toMap()["id"].toString();
//        members.removeIf([=](QList<RoomMember *>::Iterator memberIter) {
//            return (*memberIter)->getUserId() == id;
//        });
        for (auto member : members) {
            if (member->getUserId() == id) {
                members.removeAll(member);
                break;
            }
        }

        break;
    }

    emit memberLeaved();
}

void VideoRoomManager::startWatching(const QVariantMap &) {
    watcher->togglePlay();
}

void VideoRoomManager::stopWatching(const QVariantMap &) {
    watcher->togglePlay();
}

void VideoRoomManager::changeVideoContent(const QVariantMap &response) {
    // требуется проверка валидности урла
    QString src = response["src"].toString();
    QString link = YoutubeWatcher::getLinkByVideoId(src);
    watcher->setContentPath(link);
}

void VideoRoomManager::changeVideoContent(const QString &url) {
    // требуется проверка валидности урла
    networkManager->sendContentChangedRequest(url);
    QString link = YoutubeWatcher::getLinkByVideoId(url);
    watcher->setContentPath(link);
}

void VideoRoomManager::rewindTo(int timeStamp) {
    // передаем запрос к webEngine
}

void VideoRoomManager::kickMember(RoomMember *) {
    // roomMembers.remove_if(...)
    // emit memeberKicked
}

void VideoRoomManager::acceptNewMember(const QVariantMap &newMemberInfo) {
    for (auto viewerInfo : newMemberInfo["viewers"].toList()) {
        RoomMember *member = new VideoRoomMember(viewerInfo.toMap()["nick"].toString(), viewerInfo.toMap()["id"].toString());
        members.push_back(member);
        break;
    }

    emit newMember();
}

QString VideoRoomManager::getRoomId() {
    return roomId;
}

const QList<RoomMember *> &VideoRoomManager::getMembersList() {
    return members;
}

void VideoRoomManager::sendMessage() {

}


void VideoRoomManager::updateRoomState() {

}

VideoRoomManager::~VideoRoomManager() {}
