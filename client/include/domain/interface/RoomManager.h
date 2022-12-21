#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include "include/domain/models/interface/RoomMember.h"

#include <QObject>


class RoomManager : public QObject {
    Q_OBJECT
public:
//    virtual ~RoomManager();

    virtual void changeVideoContent(const QString &url) = 0;

    virtual void rewindTo(int timeStamp) = 0;

    virtual void kickMember(RoomMember *) = 0;

    virtual QString getRoomId() = 0;

    virtual const QList<RoomMember *> &getMembersList() = 0;

    virtual void sendMessage() = 0;

    virtual void updateRoomState() = 0;

    virtual void leave() = 0;
public slots:
    virtual void checkRoomState() = 0;
    virtual void acceptNewMember(const QVariantMap &) = 0;
    virtual void removeMember(const QVariantMap &) = 0;
    virtual void changeVideoContent(const QVariantMap &) = 0;
    virtual void startWatching(const QVariantMap &) = 0;

    virtual void stopWatching(const QVariantMap &) = 0;
signals:
    void memberLeaved();
    void newMember();

};

#endif // ROOMMANAGER_H
