#include "include/domain/AppAutorizationManager.h"
#include "include/network/NetworkManager.h"
#include "ui_base.h"

#include "include/UI/Base.h"


Base::Base(QWidget *parent) : QMainWindow(parent),
                              ui(new Ui::Base),
                              authManager(createAuthorizationManager()),
                              networkManager(NetworkManager::getInstance()) {
    loginWidget = new StartWidget(authManager);
    loadWidget = new LoadingWidget();
    mainWidget = new WatchUpApp();
    ui->setupUi(this);
    openLoadingWidget();

    connect(networkManager, SIGNAL(sessionStarted()), this, SLOT(openLoginWidget()));
    connect(networkManager, SIGNAL(sessionInterrupted()), this, SLOT(openLoadingWidget()));
    connect(loginWidget, SIGNAL(authorized()), this, SLOT(openMainWidget()));

//    startApp();
}

Base::~Base() {
    delete ui;

    delete authManager;
    delete networkManager;

    delete loginWidget;
    delete mainWidget;
    delete loadWidget;
}

void Base::openLoadingWidget() {
    ui->mainStackedWidget->addWidget(loadWidget);
    ui->mainStackedWidget->setCurrentWidget(loadWidget);
    qDebug() << ui->mainStackedWidget->currentWidget();
}

void Base::openLoginWidget() {
    qDebug() << mainWidget;
    ui->mainStackedWidget->addWidget(mainWidget);
    ui->mainStackedWidget->setCurrentWidget(mainWidget);
}

void Base::openMainWidget() {
    ui->mainStackedWidget->addWidget(mainWidget);
    ui->mainStackedWidget->setCurrentWidget(mainWidget);
}

//void Base::openRegistrationWidget() {}

//void Base::startApp() {
//    if (!authManager->isThereAuthorizedUser()) {
//        ui->mainStackedWidget->addWidget(loginWidget);
//        ui->mainStackedWidget->setCurrentWidget(loginWidget);
//    } else {
//        ui->mainStackedWidget->addWidget(mainWidget);
//        ui->mainStackedWidget->setCurrentWidget(mainWidget);
//    }
//}

AuthorizationManager *Base::createAuthorizationManager() {
    return new AppAuthorizationManager();
}


