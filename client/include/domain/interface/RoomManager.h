#ifndef ROOMMANAGER_H
#define ROOMMANAGER_H

#include "include/UI/YoutubeWatcher.h"
#include "include/domain/models/interface/RoomMember.h"

#include <QObject>


class RoomManager : public QObject {
    Q_OBJECT
public:
    virtual ~RoomManager() = default;

    virtual void changeWatcher(const QString &wactherType) = 0;

    virtual void reconnect() = 0;

    virtual void changeVideoContent(const QString &url) = 0;

    virtual void kickMember(RoomMember *) = 0;

    virtual QString getRoomId() = 0;

    virtual const QList<RoomMember *> &getMembersList() = 0;

    virtual void sendMessage() = 0;

    virtual void leave() = 0;

    virtual QString convertTimeStampToString(int timeStamp) = 0;

    virtual int convertTimeStampToInt(QString timeStamp) = 0;

    virtual void sync() = 0;
public slots:
    virtual void changeWatcher(const QVariantMap &request) = 0;
    virtual void updateRoomState() = 0;
    virtual void rewindTo(const QVariantMap &) = 0;
    virtual void checkRoomState() = 0;
    virtual void acceptNewMember(const QVariantMap &) = 0;
    virtual void removeMember(const QVariantMap &) = 0;
    virtual void changeVideoContent(const QVariantMap &) = 0;
    virtual void startWatching(const QVariantMap &) = 0;
    virtual void stopWatching(const QVariantMap &) = 0;
    virtual void acceptPing(const QVariantMap &) = 0;
    virtual void acceptPong(const QVariantMap &request) = 0;
    virtual void updatePlayerState() = 0;
signals:
    void memberLeaved();
    void newMember();
    void updateMemebersSyncStatus();
};

#endif // ROOMMANAGER_H
