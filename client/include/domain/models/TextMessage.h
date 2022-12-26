#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "include/domain/models/interface/Message.h"


class TextMessage : public Message {
public:
    TextMessage(QString text, QString time, QString sender);
    ~TextMessage() = default;
    TextMessage(TextMessage &message) = default;
    TextMessage(TextMessage &&message);
    TextMessage &operator=(TextMessage &message) = default;
    TextMessage &operator=(TextMessage &&message);

    virtual QString messageContent() override;

    virtual QString messageTime() override;

    virtual QString messageSender() override;

private:
    QString text;
    QString time;
    QString sender;
};


#endif // TEXTMESSAGE_H
