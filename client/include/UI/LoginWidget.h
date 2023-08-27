#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>

#include "include/domain/AppAutorizationManager.h"

namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    StartWidget(AppAuthorizationManager *authManager, QWidget *parent = nullptr);
    ~StartWidget();

signals:
    void authorized();
    void registerSignal();

private Q_SLOTS:
    void getAuthStatus(AuthenticationStatus);
    void authTry();

private:
    Ui::StartWidget *ui;
    AppAuthorizationManager *authManager;
};

#endif // STARTWIDGET_H
