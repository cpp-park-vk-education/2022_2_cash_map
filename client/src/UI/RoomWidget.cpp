#include "include/UI/RoomWidget.h"
#include "include/UI/ChatMessageWidget.h"
#include "include/UI/CustomWebView.h"
#include "include/domain/RoomChatManager.h"
#include "include/domain/VideoRoomManager.h"
#include "qclipboard.h"
#include "ui_roomwidget.h"


RoomWidget::RoomWidget(Room *room, QWidget *parent) : QWidget(parent),
                                                      ui(new Ui::RoomWidget) {
    ui->setupUi(this);

    webView = new CustomWebView(this);
    webView->setMouseTracking(true);

    watcher = new YoutubeWatcher(webView);
    manager = new VideoRoomManager(room, watcher);
    chatManager = new RoomChatManager();

    ui->videoWatcherStackedWidget->addWidget(webView);
    ui->videoWatcherStackedWidget->setCurrentWidget(webView);

    connect(ui->leaveButton, SIGNAL(clicked()), this, SLOT(leaveRoom()));

    connect(webView, SIGNAL(playerStateMightChanged()), manager, SLOT(checkRoomState()));

    connect(ui->copyLinkButton, SIGNAL(clicked()), this, SLOT(copyRoomId()));

    connect(manager, SIGNAL(newMember()), this, SLOT(updateMembersList()));
    connect(manager, SIGNAL(memberLeaved()), this, SLOT(updateMembersList()));

    connect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

    connect(chatManager, SIGNAL(messageReceived(Message*)), this, SLOT(updateChat(Message*)));

    updateMembersList();

}

void RoomWidget::updateChat(Message* message) {
    qDebug() << "IAM HERE!!";
    qDebug() << message->messageContent();
    ChatMessageWidget *messageWidget = new ChatMessageWidget(message->messageSender(), message->messageContent(), message->messageTime());
    QListWidgetItem *item = new QListWidgetItem(ui->chatListWidget);
    item->setSizeHint(messageWidget->sizeHint());
    ui->chatListWidget->addItem(item);
    ui->chatListWidget->setItemWidget(item, messageWidget);
}

void RoomWidget::sendMessage() {
    QString message = ui->messageLineEdit->text();
    chatManager->sendMessage(message);
}

void RoomWidget::updateMembersList() {
    const QList<RoomMember *> members = manager->getMembersList();
    ui->membersListWidget->clear();
    for (auto member : members) {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(member->getUsername());
        item->setIcon(QPixmap(":resources/icons/green point.png"));
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
    qDebug() << newUrl;
    manager->changeVideoContent(newUrl);
}


void RoomWidget::leaveRoom() {
    manager->leave();
    emit leaved();
}


RoomWidget::~RoomWidget() {
    delete ui;
    delete watcher;
    delete webView;
    delete manager;
}
