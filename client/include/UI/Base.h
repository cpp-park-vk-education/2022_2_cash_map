#ifndef BASE_H
#define BASE_H

#include "include/UI/RegisterWidget.h"
#include "include/UI/WatchUpApp.h"
#include "LoginWidget.h"
#include "include/network/NetworkManager.h"
#include "include/UI/LoadingWidget.h"
#include <QMainWindow>
#include "include/domain/AppAutorizationManager.h"
#include "include/domain/models/AppUser.h"

QT_BEGIN_NAMESPACE
namespace Ui {class Base;}
QT_END_NAMESPACE

class Base : public QMainWindow
{
    Q_OBJECT

public:
    explicit Base(QWidget *parent = nullptr);
    ~Base();

public slots:
    void processLogout(AuthenticationStatus status);
    void processSessionStart();
    void stopTimer();
    void openMainWidget();
    void openLoginWidget();
    void openLoadingWidget();
    void openRegisterWidget();

private:
    Ui::Base *ui;

    User *user;

    QTimer timer;

    AppAuthorizationManager *authManager;
    NetworkManager *networkManager;

    StartWidget *loginWidget;
    RegisterWidget *registerWidget;
    WatchUpApp *mainWidget;
    LoadingWidget *loadWidget;

    AppAuthorizationManager *createAuthorizationManager();

    void startApp();
};

#endif // BASE_H
