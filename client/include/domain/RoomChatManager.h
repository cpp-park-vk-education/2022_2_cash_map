#ifndef ROOMCHATMANAGER_H
#define ROOMCHATMANAGER_H

#include "include/domain/models/interface/Message.h"
#include "include/domain/interface/ChatManager.h"


#include <queue>


class RoomChatManager : public ChatManager {
public:
    RoomChatManager() = default;
    ~RoomChatManager() = default;

    virtual void sendMessage(Message *message) override;
private:
    std::queue<Message *> messagesContainer;
};


#endif // ROOMCHATMANAGER_H
