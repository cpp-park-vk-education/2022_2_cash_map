#include "include/domain/VideoRoomManager.h"
#include "include/UI/RutubeWatcher.h"
#include "include/domain/models/VideoRoomMember.h"

#include <QApplication>


VideoRoomManager::VideoRoomManager(Room *room, IVideoWatcher *watcher) : startState(watcher->getState()),
                                                              watcher(watcher),
                                                              networkManager(NetworkManager::getInstance()),
                                                              room(room) {


    connect(networkManager, SIGNAL(newMemberSignal(const QVariantMap &)), this, SLOT(acceptNewMember(const QVariantMap &)));
    connect(networkManager, SIGNAL(leaveSignal(const QVariantMap &)), this, SLOT(removeMember(const QVariantMap &)));

    connect(networkManager, SIGNAL(contentChangedSignal(const QVariantMap &)), this, SLOT(changeVideoContent(const QVariantMap &)));

    connect(networkManager, SIGNAL(playSignal(const QVariantMap &)), this, SLOT(startWatching(const QVariantMap &)));
    connect(networkManager, SIGNAL(pauseSignal(const QVariantMap &)), this, SLOT(stopWatching(const QVariantMap &)));

    connect(networkManager, SIGNAL(rewindSignal(const QVariantMap &)), this, SLOT(rewindTo(const QVariantMap &)));

    connect(networkManager, SIGNAL(pingSignal(const QVariantMap &)), this, SLOT(acceptPing(const QVariantMap &)));

    connect(networkManager, SIGNAL(pongSignal(const QVariantMap &)), this, SLOT(acceptPong(const QVariantMap &)));

    connect(networkManager, SIGNAL(serviceChangedSignal(const QVariantMap &)), this, SLOT(changeWatcher(const QVariantMap &)));

    connect(&timer, SIGNAL(timeout()), this, SLOT(updatePlayerState()));
    timer.start(3000);

    if (room->getSource() != "") {
        QString id = watcher->getVideoIdByRawLink(room->getSource());
        QString link = watcher->getLinkByVideoId(id);
        watcher->setContentPath(link);
    }
}

void VideoRoomManager::changeWatcher(IVideoWatcher *newWatcher, const QString &wactherType) {
    delete watcher;
    watcher = newWatcher;

    networkManager->sendServiceChangedRequest(wactherType);
    room->setService(wactherType);

    startState = watcher->getState();
}

void VideoRoomManager::changeWatcher(const QVariantMap &request) {
    if (request["code"].toString() == "") {
        delete watcher;
        QString service = request["service"].toString();
        QWebEngineView *view = new CustomWebView();
        if (service == "rutube") {
            watcher = new RutubeWatcher(view);
        } else {
            watcher = new YoutubeWatcher(view);
        }

        startState = watcher->getState();
        room->setService(service);
        emit changeWebViewWidget(view, service);
    }
}

void VideoRoomManager::checkRoomState() {

    qDebug() << "old state: " << startState.playing;
    PlayerState state = watcher->getState();

    state.playing = watcher->isPlaying();
    state.timestamp = watcher->getCurrentTime();
    state.speed = watcher->getCurrentSpeed();

    qDebug() << "new state: " << state.playing;
    if (state.playing != startState.playing && state.playing == false) {
        networkManager->sendPauseRequest(convertTimeStampToString(state.timestamp));
    } else if (state.playing != startState.playing && state.playing == true) {
        networkManager->sendPlayRequest();
    } else if (state.speed != startState.speed) {

    } else if (abs(startState.timestamp - state.timestamp) > 5) {
        qDebug() << "REWIND!!!!";
        qDebug() << abs(startState.timestamp - state.timestamp);
        networkManager->sendRewindRequest(convertTimeStampToString(state.timestamp));
    }

    startState = state;
}

void VideoRoomManager::updatePlayerState() {
    startState.timestamp = watcher->getCurrentTime();
}

void VideoRoomManager::leave() {
    timer.stop();
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
    qDebug() << "START TEST";
    qDebug() << "WATCHER STATE: " << watcher->isPlaying();
    qDebug() << "CODE: " << response["code"].toString();
    if (response["code"].toString() == "" && !watcher->isPlaying()) {
        watcher->togglePlay();
        startState.playing = true;
    } else if (response["code"].toString() != "200") {
        watcher->togglePlay();
        startState.playing = false;
    }
}

void VideoRoomManager::stopWatching(const QVariantMap &response) {
    if (response["code"].toString() == "" && watcher->isPlaying()) {
        watcher->togglePlay();
        startState.playing = false;
    } else if (response["code"].toString() != "200") {
        watcher->togglePlay();
        startState.playing = true;
    }

}

void VideoRoomManager::changeVideoContent(const QVariantMap &response) {
    // требуется проверка валидности урла
    if (response["code"].toString() != "200") {
        QString src = response["src"].toString();
        QString id = watcher->getVideoIdByRawLink(src);
        QString link = watcher->getLinkByVideoId(id);
        watcher->setContentPath(link);

        startState.playing = false;
        startState.timestamp = 0;
    }
}

void VideoRoomManager::changeVideoContent(const QString &url) {
    // требуется проверка валидности урла
    networkManager->sendContentChangedRequest(url);
    QString id = watcher->getVideoIdByRawLink(url);
    QString link = watcher->getLinkByVideoId(id);
    watcher->setContentPath(link);

    startState.playing = false;
    startState.timestamp = 0;
}

void VideoRoomManager::rewindTo(const QVariantMap &response) {
    int timeStamp = convertTimeStampToInt(response["time"].toString());
    qDebug() << "REWIND TO " << timeStamp;
    if (response["code"].toString() == "") {
        watcher->setCurrentTime(timeStamp);
    }
}

void VideoRoomManager::sync() {
    networkManager->sendRewindRequest(convertTimeStampToString(watcher->getCurrentTime()));
}

void VideoRoomManager::kickMember(RoomMember *) {
    // roomMembers.remove_if(...)
    // emit memeberKicked
}

void VideoRoomManager::acceptNewMember(const QVariantMap &newMemberInfo) {
    for (auto viewerInfo : newMemberInfo["viewers"].toList()) {
        RoomMember *member = new VideoRoomMember(viewerInfo.toMap()["nick"].toString(), viewerInfo.toMap()["id"].toString(), "00:00:00");
        room->addMember(member);
        break;
    }

    emit newMember();
}

void VideoRoomManager::acceptPong(const QVariantMap &request) {
    // надо переделать в QHash
    QString userId;
    QString time;
    QList<RoomMember *> members = getMembersList();
    for (auto viewerInfo : request["viewers"].toList()) {
        userId = request["id"].toString();
        time = request["time"].toString();

        for (auto member : members) {
            if (member->getUserId() == userId) {
                member->setTimeStamp(time);
                break;
            }
        }
    }




    emit updateMemebersSyncStatus();
}

void VideoRoomManager::acceptPing(const QVariantMap &request) {
    QString time = convertTimeStampToString(watcher->getCurrentTime());
    networkManager->sendPongRequest(time, request["server_time"].toString());
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
    delete watcher;
}
