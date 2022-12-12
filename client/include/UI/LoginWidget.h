#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>

#include "include/domain/interface/AuthorizationManager.h"

namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    StartWidget(AuthorizationManager *authManager, QWidget *parent = nullptr);
    ~StartWidget();

signals:
    void authorized();

private Q_SLOTS:
    void authTry();

private:
    Ui::StartWidget *ui;
    AuthorizationManager *authManager;
};

#endif // STARTWIDGET_H
