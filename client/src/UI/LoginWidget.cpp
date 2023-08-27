#include "include/UI/LoginWidget.h"
#include "ui_startwidget.h"

StartWidget::StartWidget(AppAuthorizationManager *authManager, QWidget *parent) : QWidget(parent),
                                                                               ui(new Ui::StartWidget),
                                                                               authManager(authManager) {
    ui->setupUi(this);

    connect(ui->enterButton, SIGNAL(clicked()), this, SLOT(authTry()));
    connect(ui->registerButton, SIGNAL(clicked()), this, SIGNAL(registerSignal()));
    connect(authManager, SIGNAL(authResponseSignal(AuthenticationStatus)), this, SLOT(getAuthStatus(AuthenticationStatus)));
}

void StartWidget::getAuthStatus(AuthenticationStatus status) {
    if (status == Authorized) {
        emit authorized();
    } else if (status == IncorrectLoginOrPassword) {
        ui->errorLabel->setText("Incorrect login or password");
    }
}

void StartWidget::authTry() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    authManager->authenticateUser(login, password);
}

StartWidget::~StartWidget() {
    delete ui;
}
