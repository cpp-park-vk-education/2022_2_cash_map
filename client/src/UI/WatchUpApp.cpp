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

    connect(manager, SIGNAL(succesfullyOpenedRoom(Room *)), this, SLOT(showNewRoomWidget(Room *)));
    connect(manager, SIGNAL(succesfullyJoinedRoom(Room *)), this, SLOT(showExistingingRoomWidget(Room *)));
    connect(manager, SIGNAL(failedOpeningRoom()), this, SLOT(showFailureWindow()));

    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchVideoByLink()));
}

void WatchUpApp::reloadContext() {
    if (roomWidget != nullptr) {
        roomWidget->rejoin();
    }
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

void WatchUpApp::showExistingingRoomWidget(Room *room) {
    ui->roomCreatingStatusLabel->clear();
    if (roomWidget != nullptr) { // при реконнекте объект комнаты надо пересоздать
        delete roomWidget;
        roomWidget = nullptr;
    }
    roomWidget = new RoomWidget(room);
    connect(roomWidget, SIGNAL(leaved()), this, SLOT(closeRoom()));

    ui->stackedWidget->addWidget(roomWidget);
    ui->stackedWidget->setCurrentWidget(roomWidget);
}

void WatchUpApp::showNewRoomWidget(Room *room) {
    ui->roomCreatingStatusLabel->clear();
    roomWidget = new RoomWidget(room);
    connect(roomWidget, SIGNAL(leaved()), this, SLOT(closeRoom()));

    qDebug() << room->getMembers()[0]->getUsername();
    ui->stackedWidget->addWidget(roomWidget);
    ui->stackedWidget->setCurrentWidget(roomWidget);
}

void WatchUpApp::showFailureWindow() {
    ui->roomCreatingStatusLabel->setText("Failed to open room");
}

void WatchUpApp::searchVideoByLink() {
    QString newUrl = ui->searchLineEdit->text();
    if (roomWidget != nullptr) {
        roomWidget->changeVideo(newUrl);
    }
}


WatchUpApp::~WatchUpApp() {
    delete ui;
    delete roomWidget;
    delete manager;
}

