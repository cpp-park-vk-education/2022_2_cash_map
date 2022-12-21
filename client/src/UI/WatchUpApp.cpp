#include "include/UI/WatchUpApp.h"
#include "ui_watchupapp.h"
#include <iostream>


WatchUpApp::WatchUpApp(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::WatchUpApp),
                                          roomWidget(nullptr) {
    ui->setupUi(this);
    ui->youtubeButton->setIcon(QPixmap(QString::fromUtf8(":resources/icons/youtube_icon.png")));
    manager = new MainWidgetManager();

    connect(ui->logoutButton, SIGNAL(clicked()), this, SIGNAL(logout()));

    connect(ui->createRoomButton, SIGNAL(clicked()), this, SLOT(openRoom()));
    connect(ui->joinButton, SIGNAL(clicked()), this, SLOT(enterRoom()));

    connect(manager, SIGNAL(succesfullyOpenedRoom(const QString &)), this, SLOT(showNewRoomWidget(const QString &)));
    connect(manager, SIGNAL(succesfullyJoinedRoom(const QList<RoomMember *>)), this, SLOT(showExistingingRoomWidget(const QList<RoomMember *>)));
    connect(manager, SIGNAL(failedOpeningRoom()), this, SLOT(showFailureWindow()));

    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchVideoByLink()));
}

void WatchUpApp::closeRoom() {
    ui->stackedWidget->removeWidget(roomWidget);
    delete roomWidget;
    roomWidget = nullptr;

    ui->stackedWidget->setCurrentIndex(0);
}

void WatchUpApp::openRoom() {
    QString videoId = ui->searchLineEdit->text();
    manager->createRoom(videoId);
}

void WatchUpApp::enterRoom() {
    QString roomId = ui->joinLineEdit->text();
    manager->joinRoom(roomId);
}

void WatchUpApp::showExistingingRoomWidget(const QList<RoomMember *> members) {
    QString roomId = ui->joinLineEdit->text();
    roomWidget = new RoomWidget(roomId, members);
    connect(roomWidget, SIGNAL(leaved()), this, SLOT(closeRoom()));

    ui->stackedWidget->addWidget(roomWidget);
    ui->stackedWidget->setCurrentWidget(roomWidget);
}

void WatchUpApp::showNewRoomWidget(const QString &roomId) {
    roomWidget = new RoomWidget(roomId, QList<RoomMember *>());
    connect(roomWidget, SIGNAL(leaved()), this, SLOT(closeRoom()));

    ui->stackedWidget->addWidget(roomWidget);
    ui->stackedWidget->setCurrentWidget(roomWidget);
}

void WatchUpApp::showFailureWindow() {
    qDebug() << "Failed opening";
}

void WatchUpApp::searchVideoByLink() {
    QString newUrl = ui->searchLineEdit->text();
    roomWidget->changeVideo(newUrl);
}


WatchUpApp::~WatchUpApp() {
    delete ui;
    delete roomWidget;
    delete manager;
}

