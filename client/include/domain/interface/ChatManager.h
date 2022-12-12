#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QObject>

#include "include/domain/models/interface/Message.h"


class ChatManager : public QObject {
    Q_OBJECT
public:
    virtual void sendMessage(Message *) = 0;

signals:
    void messageSent(bool);
    void newMessage(Message *);
};

#endif // CHATMANAGER_H
