#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "include/domain/models/interface/Message.h"


class TextMessage : public Message {
public:
    TextMessage(std::string text, int time, RoomMember *sender);
    ~TextMessage() = default;
    TextMessage(TextMessage &message) = default;
    TextMessage(TextMessage &&message);
    TextMessage &operator=(TextMessage &message) = default;
    TextMessage &operator=(TextMessage &&message);

    virtual std::string messageContent() override;

    virtual int messageTime() override;

    virtual RoomMember *messageSender() override;

private:
    std::string text;
    int time;
    RoomMember *sender;
};


#endif // TEXTMESSAGE_H
