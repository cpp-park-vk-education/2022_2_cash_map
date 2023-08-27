#include "include/domain/models/TextMessage.h"


TextMessage::TextMessage(QString text, QString time, QString sender) : text(text), time(time), sender(sender) {};

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

QString TextMessage::messageContent() {
    return text;
}

QString TextMessage::messageTime() {
    return time;
};

QString TextMessage::messageSender() {
    return sender;
};
