#include "include/UI/RoomWidget.h"
#include "include/UI/ChatMessageWidget.h"
#include "include/UI/CustomWebView.h"
#include "include/UI/RutubeWatcher.h"
#include "include/domain/RoomChatManager.h"
#include "include/domain/VideoRoomManager.h"
#include "qclipboard.h"
#include "ui_roomwidget.h"


RoomWidget::RoomWidget(Room *room, QWidget *parent) : QWidget(parent),
                                                      ui(new Ui::RoomWidget) {
    ui->setupUi(this);
    ui->chatListWidget->setSizeAdjustPolicy(QListWidget::AdjustToContents);

    ui->youtubeButton->setIcon(QPixmap(QString::fromUtf8(":resources/icons/youtube_icon.png")));
    ui->rutubeButton->setIcon(QPixmap(QString::fromUtf8(":resources/icons/rutube_icon.png")));

    webView = new CustomWebView(this);
    webView->setMouseTracking(true);

    if (room->getService() == "rutube") {
        watcher = new RutubeWatcher(webView);
        ui->rutubeButton->setChecked(true);
    } else if (room->getService() == "youtube") {
        watcher = new YoutubeWatcher(webView);
        ui->youtubeButton->setChecked(true);
    }

    manager = new VideoRoomManager(room, watcher);
    chatManager = new RoomChatManager();

    connect(manager, SIGNAL(updatedWebView(QWebEngineView *)), this, SLOT(updateWebView(QWebEngineView *)));

    ui->videoWatcherStackedWidget->addWidget(webView);
    ui->videoWatcherStackedWidget->setCurrentWidget(webView);

    connect(ui->youtubeButton, SIGNAL(clicked(bool)), this, SLOT(changeWatcher(bool)));
    connect(ui->rutubeButton, SIGNAL(clicked(bool)), this, SLOT(changeWatcher(bool)));

    connect(ui->syncButton, SIGNAL(clicked()), this, SLOT(askForSync()));

    connect(ui->leaveButton, SIGNAL(clicked()), this, SLOT(leaveRoom()));

    connect(ui->copyLinkButton, SIGNAL(clicked()), this, SLOT(copyRoomId()));

    connect(manager, SIGNAL(newMember()), this, SLOT(updateMembersList()));
    connect(manager, SIGNAL(memberLeaved()), this, SLOT(updateMembersList()));
    connect(manager, SIGNAL(updateMemebersSyncStatus()), this, SLOT(updateMembersList()));

    connect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

    connect(chatManager, SIGNAL(messageReceived(Message*)), this, SLOT(updateChat(Message*)));


    updateMembersList();

}


void RoomWidget::changeWatcher(bool checked) {
    if (checked) {
        QObject *senderObject = sender();
        QString watcherType;
        if (senderObject == ui->youtubeButton) {
            watcherType = "youtube";
        } else if (senderObject == ui->rutubeButton) {
            watcherType = "rutube";
        }

        manager->changeWatcher(watcherType);
    }
}

void RoomWidget::updateWebView(QWebEngineView *newView) {
    webView = newView;
    ui->videoWatcherStackedWidget->addWidget(newView);
    ui->videoWatcherStackedWidget->setCurrentWidget(newView);
    connect(webView, SIGNAL(playerStateMightChanged()), manager, SLOT(checkRoomState()));
}

void RoomWidget::askForSync() {
    manager->sync();
}


void RoomWidget::updateChat(Message* message) {
    ChatMessageWidget *messageWidget = new ChatMessageWidget(message->messageSender(), message->messageContent(), message->messageTime());
    QListWidgetItem *item = new QListWidgetItem(ui->chatListWidget);
    item->setSizeHint(messageWidget->sizeHint());
    ui->chatListWidget->addItem(item);
    ui->chatListWidget->setItemWidget(item, messageWidget);
    ui->chatListWidget->scrollToItem(item);
}

void RoomWidget::sendMessage() {
    QString message = ui->messageLineEdit->text();
    ui->messageLineEdit->clear();
    chatManager->sendMessage(message);
}

void RoomWidget::updateMembersList() {
    const QList<RoomMember *> members = manager->getMembersList();
    ui->membersListWidget->clear();

    int perfectTiming = 0;
    for (auto member : members) {
        int timing = manager->convertTimeStampToInt(member->getCurrentTimeStamp());
        if (timing > perfectTiming) {
            perfectTiming = timing;
        }
    }

    qDebug() << "PERFECT: " << perfectTiming;

    for (auto member : members) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(member->getUsername());
        int timing = manager->convertTimeStampToInt(member->getCurrentTimeStamp());
        qDebug() << "TIMEING: " << timing;
        if (perfectTiming - timing > 2) {
            item->setIcon(QPixmap(":resources/icons/red point.png"));
        } else {
            item->setIcon(QPixmap(":resources/icons/green point.png"));
        }
        ui->membersListWidget->addItem(item);
    }
}


void RoomWidget::rejoin() {
    manager->reconnect();
}


void RoomWidget::copyRoomId() {
    QString roomId = manager->getRoomId();
    QApplication::clipboard()->setText(roomId);
}

void RoomWidget::changeVideo(const QString &newUrl) {
    manager->changeVideoContent(newUrl);
}


void RoomWidget::leaveRoom() {
    manager->leave();
    emit leaved();
}


RoomWidget::~RoomWidget() {
    delete ui;
    delete manager;
    delete chatManager;
}
