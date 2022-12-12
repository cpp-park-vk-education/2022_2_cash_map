#include "include/domain/MainWidgetManager.h"


MainWidgetManager::MainWidgetManager(QObject *parent) : QObject(parent){
    networkManager = NetworkManager::getInstance();
}


void MainWidgetManager::createRoom() {
    networkManager->sendCreateRoomRequest();
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
