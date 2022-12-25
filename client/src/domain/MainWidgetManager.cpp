#include "include/domain/MainWidgetManager.h"

#include "include/domain/models/VideoRoom.h"

#include "include/domain/models/VideoRoomMember.h"

#include <include/domain/models/AppUser.h>

MainWidgetManager::MainWidgetManager(QObject *parent) : QObject(parent){
    networkManager = NetworkManager::getInstance();

    connect(networkManager, SIGNAL(joinSignal(const QVariantMap &)), this, SLOT(manageResponse(const QVariantMap &)));
    connect(networkManager, SIGNAL(createSignal(const QVariantMap &)), this, SLOT(manageResponse(const QVariantMap &)));
}


void MainWidgetManager::manageResponse(const QVariantMap &response) {
    if (response["type"].toString() == "join" && response["code"].toString() == "200") {
        emit succesfullyJoinedRoom(createRoomObject(response));
    } else if (response["type"].toString() == "join") { //&& response["code"] == "400" {
        emit failedOpeningRoom();
    }

    if (response["type"].toString() == "create" && response["code"].toString() == "200") {
        emit succesfullyOpenedRoom(createRoomObject(response));
    } else if (response["type"].toString() == "create") {
        emit failedOpeningRoom();
    }
}

Room *MainWidgetManager::createRoomObject(const QVariantMap &response) {
    QList<RoomMember *> members;
    for (auto viewerInfo : response["viewers"].toList()) {
        RoomMember *member = new VideoRoomMember(viewerInfo.toMap()["nick"].toString(),
                                                 viewerInfo.toMap()["id"].toString(),
                                                 response["time"].toString());
        members.push_back(member);
    }
    QString timeStamp = response["time"].toString() != "" ? response["time"].toString() : "00:00:00";
    Room *room = new VideoRoom(new VideoRoomMember(User::getInstance()->getUserName(), User::getInstance()->getLogin(), timeStamp),
                                                   response["room_id"].toString(),
                                                   members, response["src"].toString(),
                                                   response["state"].toBool());
    return room;
}


void MainWidgetManager::createRoom(const QString &videoId) {
    networkManager->sendCreateRoomRequest(videoId);
}

void MainWidgetManager::joinRoom(const QString &roomId) {
    networkManager->sendJoinRoomRequest(roomId);
}

void MainWidgetManager::leaveRoom() {
    networkManager->sendLeaveRoomRequest();
}
void MainWidgetManager::playVideo() {
    networkManager->sendPlayRequest();
}
