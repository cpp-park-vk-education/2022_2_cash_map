#include "include/UI/WatchUpApp.h"
#include "ui_watchupapp.h"
#include <iostream>
#include "include/domain/YoutubeItemCollector.h"
#include "include/UI/SearchListWidgetItem.h"


WatchUpApp::WatchUpApp(QWidget *parent) : QMainWindow(parent) , ui(new Ui::WatchUpApp) {
    ui->setupUi(this);

    searchCollector = createSearchItemCollector();
    authManager = createAuthorizationManager();
    // временное решение
    ui->openRoomButton->setEnabled(false);
    ui->logOutButton->setEnabled(false);

    connect(ui->createRoomButton, SIGNAL(clicked()), this, SLOT(createRoom()));
    connect(ui->openRoomButton, SIGNAL(clicked()), this, SLOT(openRoom()));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(showSearchResults()));

    ui->stackedWidget->insertWidget(0, &startWidget);
    ui->stackedWidget->insertWidget(1, &roomWidget);

    ui->stackedWidget->setCurrentIndex(0);
}

WatchUpApp::~WatchUpApp() {
    delete ui;
}

void WatchUpApp::createRoom() {
    // инициализируем комнату
    if (authManager->isUserAuthorized()) {
        ui->stackedWidget->setCurrentIndex(1);
        ui->openRoomButton->setEnabled(true);
    } else {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void WatchUpApp::openRoom() {
    // просто входим в комнату
    ui->stackedWidget->setCurrentIndex(1);
}

void WatchUpApp::showSearchResults() {
    ui->listWidget->clear();

    std::vector<SearchItem *> modelItems = searchCollector->prepareSearchResult(ui->searchLineEdit->text().toStdString());
    for (auto item : modelItems) {
        QListWidgetItem *emptyItem = new QListWidgetItem();
        SearchListWidgetItem *widget = new SearchListWidgetItem();

        widget->setHeaderText(item->title().c_str());
        widget->setDescription(item->shortDescription().c_str());
        widget->setPreviewImage(item->previewImage().c_str());
        widget->setVideoLink(item->videoLink().c_str());

        ui->listWidget->addItem(emptyItem);
        ui->listWidget->setItemWidget(emptyItem, widget);
    }
}

SearchItemCollector *WatchUpApp::createSearchItemCollector() {
    if (ui->youtubeButton->isChecked()) {
        return new YoutubeItemCollector();
    }
    return nullptr;
}

AuthorizationManager *WatchUpApp::createAuthorizationManager() {
    return new AppAuthorizationManager();
}
