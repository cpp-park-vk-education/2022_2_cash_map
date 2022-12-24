#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QWidget>
#include "include/UI/YoutubeWatcher.h"
#include "include/domain/interface/ChatManager.h"
#include "include/domain/interface/RoomManager.h"
#include "include/domain/models/interface/Room.h"

namespace Ui {
class RoomWidget;
}

class RoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomWidget(Room *room, QWidget *parent = nullptr);
    ~RoomWidget();

    void rejoin();
public slots:
    void updateChat(Message*);
    void sendMessage();
    void leaveRoom();
    void changeVideo(const QString &newUrl);
    void copyRoomId();
    void updateMembersList();
signals:
    void leaved();

private:
    Ui::RoomWidget *ui;
    RoomManager *manager;
    ChatManager *chatManager;

    YoutubeWatcher *watcher;
    CustomWebView *webView;

};

#endif // ROOMWIDGET_H
