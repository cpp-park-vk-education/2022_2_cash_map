#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QWidget>
#include "include/UI/YoutubeWatcher.h"
#include "include/domain/interface/RoomManager.h"

namespace Ui {
class RoomWidget;
}

class RoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomWidget(const QString &roomId, const QList<RoomMember *> members, QWidget *parent = nullptr);
    ~RoomWidget();
public slots:
    void leaveRoom();
    void changeVideo(const QString &newUrl);
    void copyRoomId();
    void updateMembersList();
signals:
    void leaved();

private:
    Ui::RoomWidget *ui;
    RoomManager *manager;

    YoutubeWatcher *watcher;
    CustomWebView *webView;

};

#endif // ROOMWIDGET_H
