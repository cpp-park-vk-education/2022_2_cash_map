#include "include/UI/WatchUpApp.h"
#include "ui_watchupapp.h"
#include <iostream>


WatchUpApp::WatchUpApp(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::WatchUpApp) {
    ui->setupUi(this);
    qDebug() << "16";
    roomWidget = new RoomWidget();
    qDebug() << "15";
    manager = new MainWidgetManager();

    // временное решение
    connect(ui->createRoomButton, SIGNAL(clicked()), this, SLOT(openRoom()));
    connect(ui->joinButton, SIGNAL(clicked()), this, SLOT(enterRoom()));
}

void WatchUpApp::openRoom() {
    qDebug() << "wqeqw";
    manager->createRoom();
    ui->stackedWidget->addWidget(roomWidget);
    ui->stackedWidget->setCurrentWidget(roomWidget);
}

void WatchUpApp::enterRoom() {
    QString roomId = ui->joinLineEdit->text();
    manager->joinRoom(roomId);
    ui->stackedWidget->addWidget(roomWidget);
    ui->stackedWidget->setCurrentWidget(roomWidget);
}


WatchUpApp::~WatchUpApp() {
    delete ui;
    delete roomWidget;
    delete manager;
}

