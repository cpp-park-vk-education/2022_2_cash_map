#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QObject>

#include "include/domain/models/interface/Message.h"


class ChatManager : public QObject {
    Q_OBJECT
public:
    virtual void sendMessage(const QString &message) = 0;
public slots:
    virtual void getNewMessage(const QVariantMap &) = 0;
signals:
    void messageReceived(Message *);
};

#endif // CHATMANAGER_H
