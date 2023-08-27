#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include "include/domain/AppAutorizationManager.h"
#include <QWidget>

namespace Ui {
class RegisterWidget;
}

class RegisterWidget : public QWidget
{
    Q_OBJECT

public slots:
    void registerUser();
    void getRegistrationStatus(RegistrationStatus);

public:
    explicit RegisterWidget(AppAuthorizationManager *authManager, QWidget *parent = nullptr);
    ~RegisterWidget();
signals:
    void registerFinished();

private:
    Ui::RegisterWidget *ui;

    AppAuthorizationManager *authManager;
};

#endif // REGISTERWIDGET_H
