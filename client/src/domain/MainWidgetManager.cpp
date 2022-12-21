#include "include/domain/MainWidgetManager.h"

#include <include/domain/models/VideoRoomMember.h>


MainWidgetManager::MainWidgetManager(QObject *parent) : QObject(parent){
    networkManager = NetworkManager::getInstance();

    connect(networkManager, SIGNAL(joinSignal(const QVariantMap &)), this, SLOT(manageResponse(const QVariantMap &)));
    connect(networkManager, SIGNAL(createSignal(const QVariantMap &)), this, SLOT(manageResponse(const QVariantMap &)));
}


void MainWidgetManager::manageResponse(const QVariantMap &response) {
    if (response["type"].toString() == "join" /*&& response["code"].toString() == "200"*/) {
        QList<RoomMember *> members;
        for (auto viewerInfo : response["viewers"].toList()) {
            RoomMember *member = new VideoRoomMember(viewerInfo.toMap()["nick"].toString(), viewerInfo.toMap()["id"].toString());
            members.push_back(member);
        }
        emit succesfullyJoinedRoom(members);
    } else if (response["type"].toString() == "join") { //&& response["code"] == "400" {
        emit failedOpeningRoom();
    }

    if (response["type"].toString() == "create" && response["code"].toString() == "200") {
        emit succesfullyOpenedRoom(response["room_id"].toString());
    } else if (response["type"].toString() == "create") {
        emit failedOpeningRoom();
    }
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
