#include "include/domain/AppAutorizationManager.h"
#include "include/network/NetworkManager.h"
#include "ui_base.h"

#include "include/UI/Base.h"


Base::Base(QWidget *parent) : QMainWindow(parent),
                              ui(new Ui::Base),
                              user(User::getInstance()),
                              networkManager(NetworkManager::getInstance()) {

    ui->setupUi(this);

    authManager = createAuthorizationManager();

    registerWidget = new RegisterWidget(authManager);
    loginWidget = new StartWidget(authManager);
    loadWidget = new LoadingWidget();
    mainWidget = new WatchUpApp();

    ui->mainStackedWidget->addWidget(loadWidget);
    ui->mainStackedWidget->addWidget(registerWidget);
    ui->mainStackedWidget->addWidget(loginWidget);
    ui->mainStackedWidget->addWidget(mainWidget);

    connect(&timer, SIGNAL(timeout()), networkManager, SLOT(recovery()));

    connect(networkManager, SIGNAL(sessionStarted()), this, SLOT(processSessionStart()));
    connect(networkManager, SIGNAL(sessionStarted()), this, SLOT(stopTimer()));
    connect(networkManager, SIGNAL(sessionInterrupted()), this, SLOT(openLoadingWidget()));

    connect(mainWidget, SIGNAL(logout()), authManager, SLOT(logout()));

    connect(authManager, SIGNAL(logoutSignal(AuthenticationStatus)), this, SLOT(processLogout(AuthenticationStatus)));

    connect(loginWidget, SIGNAL(authorized()), this, SLOT(openMainWidget()));

    connect(loginWidget, SIGNAL(registerSignal()), this, SLOT(openRegisterWidget()));

    connect(registerWidget, SIGNAL(registerFinished()), this, SLOT(openLoginWidget()));
}


void Base::processLogout(AuthenticationStatus status) {
//    if (status == AuthenticationStatus::LogoutSucceeded) {
//        user->clear();
//        ui->mainStackedWidget->setCurrentWidget(loginWidget);
//    }
    user->clear();
    ui->mainStackedWidget->setCurrentWidget(loginWidget);
}

void Base::processSessionStart() {
    if (!user->initialized()) { // если не было еще аутентификации, то пользователь не создан
        openLoginWidget();
    } else {
        authManager->authenticateUser(user->getLogin(), user->getPassword());
    }
}

void Base::stopTimer() {
    timer.stop();
}

void Base::openLoadingWidget() {
    ui->mainStackedWidget->setCurrentWidget(loadWidget);
    timer.start(6000);
}

void Base::openRegisterWidget() {
    ui->mainStackedWidget->setCurrentWidget(registerWidget);
}

void Base::openLoginWidget() {
    ui->mainStackedWidget->setCurrentWidget(loginWidget);
}

void Base::openMainWidget() {
    ui->mainStackedWidget->setCurrentWidget(mainWidget);
    mainWidget->reloadContext();
}

AppAuthorizationManager *Base::createAuthorizationManager() {
    return new AppAuthorizationManager(networkManager);
}

Base::~Base() {
    delete ui;

    delete authManager;
    delete networkManager;

    delete loginWidget;
    delete mainWidget;
    delete loadWidget;
    delete user;
}


