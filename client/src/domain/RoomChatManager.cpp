#include <queue>

#include "include/domain/RoomChatManager.h"
#include "include/domain/models/TextMessage.h"


RoomChatManager::RoomChatManager() : networkManager(NetworkManager::getInstance()) {
    connect(networkManager, SIGNAL(newMessageSignal(const QVariantMap &)), this, SLOT(getNewMessage(const QVariantMap &)));
}

void RoomChatManager::sendMessage(const QString &message) {
    networkManager->sendMessageRequest(message);

}


void RoomChatManager::getNewMessage(const QVariantMap &response) {
    Message *newMessage = new TextMessage(response["msg"].toString(), QString("00:00"), response["sender"].toString());
    messagesContainer.push(newMessage);
    qDebug() << "Inside roomchat  manager";
    emit messageReceived(newMessage);
}
