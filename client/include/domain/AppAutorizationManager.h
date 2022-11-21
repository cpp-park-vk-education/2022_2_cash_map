#ifndef APPAUTORIZATIONMANAGER_H
#define APPAUTORIZATIONMANAGER_H


#include "include/domain/interface/AuthorizationManager.h"
#include "include/domain/models/interface/User.h"

class AppAuthorizationManager : public AuthorizationManager {
public:
    AppAuthorizationManager();
    ~AppAuthorizationManager();

    virtual AuthorizationStatus authorizeUser(std::string username, std::string password) override;

    virtual bool isUserAuthorized() override;
private:
    User *user = nullptr;
};


#endif // APPAUTORIZATIONMANAGER_H
