#include "include/domain/AppAutorizationManager.h"

#include <include/domain/models/AppUser.h>


AppAuthorizationManager::AppAuthorizationManager(NetworkManager *networkManager) : networkManager(networkManager) {
    connect(networkManager, SIGNAL(authStatusSignal(const QVariantMap &)), this, SLOT(processResponse(const QVariantMap &)));
    connect(networkManager, SIGNAL(registrationStatusSignal(const QVariantMap &)), this, SLOT(processResponse(const QVariantMap &)));
}


void AppAuthorizationManager::authenticateUser(const QString &login, const QString &password) {
    networkManager->sendAuthRequest(login, password);
};

void AppAuthorizationManager::logout() {
    networkManager->sendLogoutRequest();
}

void AppAuthorizationManager::registerUser(const QString &username, const QString &login, const QString &password) {
    networkManager->sendRegistrationRequest(login, username, password);
}

void AppAuthorizationManager::processResponse(const QVariantMap &response) { // пока обработка всех кодов, кроме 200 одинаковая
    if (response["type"] == "login" && response["code"] == "200") {
        User::getInstance()->setUserInfo(response["nick"].toString(), response["login"].toString(), response["password"].toString());
        emit authResponseSignal(AuthenticationStatus::Authorized);
    } else if (response["type"] == "login") {
        qDebug() << "IncorrectLoginOrPassword";
        emit authResponseSignal(AuthenticationStatus::IncorrectLoginOrPassword);
    } else if (response["type"] == "reg" && response["code"] == "200") {
        emit registrationSignal(RegistrationStatus::Registered);
    } else if (response["type"] == "reg"){
        emit registrationSignal(RegistrationStatus::LoginInUse);
    } else if (response["type"] == "logout" && response["code"] == "200"){
        User::getInstance()->clear();
        emit logoutSignal(AuthenticationStatus::LogoutSucceeded);
    } else {
        emit logoutSignal(AuthenticationStatus::LogoutFailed);
    }
}

bool AppAuthorizationManager::isThereAuthorizedUser() {
    return false;
};
