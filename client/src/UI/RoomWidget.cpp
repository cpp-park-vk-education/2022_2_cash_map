#include "include/UI/RoomWidget.h"
#include "include/UI/CustomWebView.h"
#include "include/domain/VideoRoomManager.h"
#include "ui_roomwidget.h"


RoomWidget::RoomWidget(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::RoomWidget) {
    ui->setupUi(this);
    webView = new CustomWebView(this);
    webView->setMouseTracking(true);
    watcher = new YoutubeWatcher(webView);

    manager = new VideoRoomManager(QString("shreks"), watcher);


    ui->videoWatcherStackedWidget->addWidget(webView);
    ui->videoWatcherStackedWidget->setCurrentWidget(webView);

    connect(webView, SIGNAL(playerStateMightChanged()), manager, SLOT(checkRoomState()));

    try {
        QString id = "7oEZaljP7uY";
        QString url = YoutubeWatcher::getLinkByVideoId(id);
        watcher->setContentPath(url);
    } catch (std::runtime_error err) {

    }
}


RoomWidget::~RoomWidget() {
    delete ui;
    delete watcher;
    delete webView;
}
