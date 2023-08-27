#ifndef ROOMCHATMANAGER_H
#define ROOMCHATMANAGER_H

#include "include/domain/models/interface/Message.h"
#include "include/domain/interface/ChatManager.h"
#include "include/network/NetworkManager.h"


#include <queue>


class RoomChatManager : public ChatManager {
public:
    RoomChatManager();
    ~RoomChatManager() = default;

    virtual void sendMessage(const QString &message) override;
public slots:
    virtual void getNewMessage(const QVariantMap &) override;
private:
    NetworkManager *networkManager;
    std::queue<Message *> messagesContainer;
};


#endif // ROOMCHATMANAGER_H
