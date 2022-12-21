#ifndef VIDEOROOMMANAGER_H
#define VIDEOROOMMANAGER_H

#include "include/UI/YoutubeWatcher.h"
#include "include/domain/interface/RoomManager.h"
#include "include/network/NetworkManager.h"



class VideoRoomManager : public RoomManager {
public:
    VideoRoomManager(const QString &username, const QString &userId, YoutubeWatcher *watcher, const QString &roomId, const QList<RoomMember *> members);

    ~VideoRoomManager();

    virtual void changeVideoContent(const QString &url) override;


    virtual void rewindTo(int timeStamp) override;

    virtual void kickMember(RoomMember *) override;

    virtual QString getRoomId() override;

    virtual const QList<RoomMember *> &getMembersList() override;

    virtual void sendMessage() override;

    virtual void updateRoomState() override;

    virtual void leave() override;
public slots:
    virtual void checkRoomState() override;
    virtual void acceptNewMember(const QVariantMap &) override;
    virtual void removeMember(const QVariantMap &) override;
    virtual void changeVideoContent(const QVariantMap &) override;
    virtual void startWatching(const QVariantMap &) override;
    virtual void stopWatching(const QVariantMap &) override;

private:
    PlayerState startState;
    YoutubeWatcher *watcher;
    NetworkManager *networkManager;

    QList<RoomMember *> members;
    QString roomId;
};


#endif // VIDEOROOMMANAGER_H
