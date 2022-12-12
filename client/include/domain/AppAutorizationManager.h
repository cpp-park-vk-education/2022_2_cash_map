#ifndef APPAUTORIZATIONMANAGER_H
#define APPAUTORIZATIONMANAGER_H


#include "include/domain/interface/AuthorizationManager.h"

class AppAuthorizationManager : public AuthorizationManager {
public:
    AppAuthorizationManager() = default;
    ~AppAuthorizationManager() = default;

    virtual AuthenticationStatus authenticateUser(const QString &username, const QString &password) override;

    virtual bool isThereAuthorizedUser() override;

};


#endif // APPAUTORIZATIONMANAGER_H
