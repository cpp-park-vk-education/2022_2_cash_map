#ifndef APPAUTORIZATIONMANAGER_H
#define APPAUTORIZATIONMANAGER_H


#include "include/domain/interface/AuthorizationManager.h"

class AppAuthorizationManager : public AuthorizationManager {
    Q_OBJECT
public:
    AppAuthorizationManager(NetworkManager *networkManager);
    ~AppAuthorizationManager() = default;

    virtual void authenticateUser(const QString &login, const QString &password) override;

    virtual void registerUser(const QString &username, const QString &login, const QString &password) override;

    virtual bool isThereAuthorizedUser() override;
public slots:
    virtual void processResponse(const QVariantMap &response) override;
    virtual void logout() override;

private:
    NetworkManager *networkManager;

};


#endif // APPAUTORIZATIONMANAGER_H
