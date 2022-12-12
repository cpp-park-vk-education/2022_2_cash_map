#ifndef WATCHUPAPP_H
#define WATCHUPAPP_H

#include "RoomWidget.h"
#include "include/domain/MainWidgetManager.h"
#include "include/domain/interface/SearchItemCollector.h"
#include <QMainWindow>
#include <include/network/WatchUpServerClient.h>

QT_BEGIN_NAMESPACE
namespace Ui { class WatchUpApp; }
QT_END_NAMESPACE

class WatchUpApp : public QMainWindow {
    Q_OBJECT

public:    
    WatchUpApp(QWidget *parent = nullptr);
    ~WatchUpApp();

//    SearchItemCollector *searchCollector;
public slots:
    void openRoom();

    void enterRoom();

private:
    Ui::WatchUpApp *ui;
    RoomWidget *roomWidget;

    MainWidgetManager *manager;

    SearchItemCollector *createSearchItemCollector();

};
#endif // WATCHUPAPP_H
