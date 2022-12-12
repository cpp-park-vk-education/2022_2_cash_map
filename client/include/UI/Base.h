#ifndef BASE_H
#define BASE_H

#include "include/UI/WatchUpApp.h"
#include "include/domain/interface/AuthorizationManager.h"
#include "LoginWidget.h"
#include "include/network/NetworkManager.h"
#include "include/UI/LoadingWidget.h"
#include <QMainWindow>

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
    void openMainWidget();
    void openLoginWidget();
    void openLoadingWidget();

private:
    Ui::Base *ui;

    AuthorizationManager *authManager;
    NetworkManager *networkManager;

    StartWidget *loginWidget;
    WatchUpApp *mainWidget;
    LoadingWidget *loadWidget;

    AuthorizationManager *createAuthorizationManager();

    void startApp();
};

#endif // BASE_H
