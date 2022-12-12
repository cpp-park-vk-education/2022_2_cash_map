#include "include/domain/models/TextMessage.h"


TextMessage::TextMessage(std::string text, int time, RoomMember *sender) : text(text), time(time), sender(sender) {};

TextMessage::TextMessage(TextMessage &&message) {
    if (&message != this) {

        text = message.text;
        time = message.time;
        sender = message.sender;

        message.sender = nullptr;
    }
};

TextMessage &TextMessage::operator=(TextMessage &&message) {
    if (&message != this) {

        text = message.text;
        time = message.time;
        sender = message.sender;

        message.sender = nullptr;
    }
    return *this;
};

std::string TextMessage::messageContent() {
    return text;
}

int TextMessage::messageTime() {
    return time;
};

RoomMember *TextMessage::messageSender() {
    return sender;
};
