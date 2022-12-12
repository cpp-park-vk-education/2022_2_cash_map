#ifndef MAINWIDGETMANAGER_H
#define MAINWIDGETMANAGER_H

#include "include/network/NetworkManager.h"

class MainWidgetManager : public QObject {
    Q_OBJECT
public:
    MainWidgetManager(QObject *parent = nullptr);
    ~MainWidgetManager() = default;

public slots:
    void createRoom();
    void joinRoom(const QString &roomId);
    void leaveRoom();
    void playVideo();
signals:
    void roomReady();
    void joinReady();
    void leaveDone();
    void playDone();
private:
    NetworkManager *networkManager;

};

#endif // MAINWIDGETMANAGER_H
