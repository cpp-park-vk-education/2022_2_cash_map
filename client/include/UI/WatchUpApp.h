#ifndef WATCHUPAPP_H
#define WATCHUPAPP_H

#include "RoomWidget.h"
#include "LoginWidget.h"
#include "include/domain/AppAutorizationManager.h"
#include "include/domain/interface/AuthorizationManager.h"
#include "include/domain/interface/SearchItemCollector.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class WatchUpApp; }
QT_END_NAMESPACE

class WatchUpApp : public QMainWindow {
    Q_OBJECT

public:    
    WatchUpApp(QWidget *parent = nullptr);
    ~WatchUpApp();

    AuthorizationManager *authManager;
    SearchItemCollector *searchCollector;

private:
    Ui::WatchUpApp *ui;

    StartWidget startWidget;
    RoomWidget roomWidget;

    SearchItemCollector *createSearchItemCollector();
    AuthorizationManager *createAuthorizationManager();

private slots:
    void createRoom();
    void openRoom();
    void showSearchResults();
};
#endif // WATCHUPAPP_H
