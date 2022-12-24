#include "include/domain/VideoRoomManager.h"
#include "include/domain/models/VideoRoomMember.h"


VideoRoomManager::VideoRoomManager(Room *room, YoutubeWatcher *watcher) : startState(watcher->getState()),
                                                              watcher(watcher),
                                                              networkManager(NetworkManager::getInstance()),
                                                              room(room) {

    connect(networkManager, SIGNAL(newMemberSignal(const QVariantMap &)), this, SLOT(acceptNewMember(const QVariantMap &)));
    connect(networkManager, SIGNAL(leaveSignal(const QVariantMap &)), this, SLOT(removeMember(const QVariantMap &)));
    connect(networkManager, SIGNAL(contentChangedSignal(const QVariantMap &)), this, SLOT(changeVideoContent(const QVariantMap &)));
    connect(networkManager, SIGNAL(playSignal(const QVariantMap &)), this, SLOT(startWatching(const QVariantMap &)));
    connect(networkManager, SIGNAL(pauseSignal(const QVariantMap &)), this, SLOT(stopWatching(const QVariantMap &)));

    if (room->getSource() != "") {
        QString id = YoutubeWatcher::getVideoIdByRawLink(room->getSource());
        QString link = YoutubeWatcher::getLinkByVideoId(id);
        watcher->setContentPath(link);
    }
}

void VideoRoomManager::checkRoomState() {
    // delay
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }


    PlayerState state = watcher->getState();
    if (state.playing != startState.playing && state.playing == false) {
        networkManager->sendPauseRequest(convertTimeStampToString(state.timestamp));
    } else if (state.playing != startState.playing && state.playing == true) {
        networkManager->sendPlayRequest();
    } else if (state.speed != startState.speed) {

    }

    startState = state;
}

void VideoRoomManager::leave() {
    networkManager->sendLeaveRoomRequest();

}

void VideoRoomManager::reconnect() {
    networkManager->sendJoinRoomRequest(room->getRoomId());
}

void VideoRoomManager::removeMember(const QVariantMap &newMemberInfo) {
    for (auto viewerInfo : newMemberInfo["viewers"].toList()) {
        QString id = viewerInfo.toMap()["id"].toString();

        for (auto member : room->getMembers()) {
            if (member->getUserId() == id) {
                room->removeMember(member);
                break;
            }
        }
        break;
    }

    emit memberLeaved();
}

void VideoRoomManager::startWatching(const QVariantMap &response) {
    if (response["code"] != "200"/* && !watcher->isPlaying()*/) {
        watcher->togglePlay();
    }
}

void VideoRoomManager::stopWatching(const QVariantMap &response) {
    if (response["code"] != "200"/* && watcher->isPlaying()*/) {
        watcher->togglePlay();
    }
}

void VideoRoomManager::changeVideoContent(const QVariantMap &response) {
    // требуется проверка валидности урла
    QString src = response["src"].toString();
    QString id = YoutubeWatcher::getVideoIdByRawLink(src);
    QString link = YoutubeWatcher::getLinkByVideoId(id);
    watcher->setContentPath(link);
    startState = watcher->getState();
}

void VideoRoomManager::changeVideoContent(const QString &url) {
    // требуется проверка валидности урла
    networkManager->sendContentChangedRequest(url);
    QString id = YoutubeWatcher::getVideoIdByRawLink(url);
    QString link = YoutubeWatcher::getLinkByVideoId(id);
    watcher->setContentPath(link);
    startState = watcher->getState();
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
        room->addMember(member);
        break;
    }

    emit newMember();
}

QString VideoRoomManager::getRoomId() {
    return room->getRoomId();
}

const QList<RoomMember *> &VideoRoomManager::getMembersList() {
    return room->getMembers();
}

void VideoRoomManager::sendMessage() {

}


void VideoRoomManager::updateRoomState() {

}

int VideoRoomManager::convertTimeStampToInt(QString timeStamp) {
    int convertedTimeStamp = 0;

    int hours = timeStamp.mid(0, 2).toInt();

    int minutes = timeStamp.mid(3, 2).toInt();

    int seconds = timeStamp.mid(6, 2).toInt();

    convertedTimeStamp += hours * 3600 + minutes * 60 + seconds;

    return convertedTimeStamp;

}

QString VideoRoomManager::convertTimeStampToString(int timeStamp) {
    QString convertedTimeStamp;
    int hours = timeStamp / 3600;
    QString stringedHours = QString::fromStdString(std::to_string(hours));
    int minutes = (timeStamp - hours * 3600) / 60;
    QString stringedMinutes = QString::fromStdString(std::to_string(minutes));
    int seconds = timeStamp - hours * 3600 - minutes * 60;
    QString stringedSeconds = QString::fromStdString(std::to_string(seconds));

    if (stringedHours.length() == 1) {
        stringedHours = "0" + stringedHours;
    }
    if (stringedMinutes.length() == 1) {
        stringedMinutes = "0" + stringedMinutes;
    }
    if (stringedSeconds.length() == 1) {
        stringedSeconds = "0" + stringedSeconds;
    }

    convertedTimeStamp = stringedHours + ":" + stringedMinutes + ":" + stringedSeconds + ".00";
    qDebug() << convertedTimeStamp;
    return convertedTimeStamp;
}

VideoRoomManager::~VideoRoomManager() {
    delete room;
}
