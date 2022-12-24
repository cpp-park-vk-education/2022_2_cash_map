#include "include/UI/RegisterWidget.h"
#include "ui_registerwidget.h"


RegisterWidget::RegisterWidget(AppAuthorizationManager *authManager, QWidget *parent) : QWidget(parent),
                                                                                        ui(new Ui::RegisterWidget),
                                                                                        authManager(authManager) {
    ui->setupUi(this);
    connect(ui->registerButton, SIGNAL(clicked()), this, SLOT(registerUser()));
    connect(authManager, SIGNAL(registrationSignal(RegistrationStatus)), this, SLOT(getRegistrationStatus(RegistrationStatus)));
    connect(ui->loginButton, SIGNAL(clicked()), this, SIGNAL(registerFinished()));
}

void RegisterWidget::getRegistrationStatus(RegistrationStatus status) {
    if (status == RegistrationStatus::Registered) {
        emit registerFinished();
    }
}

void RegisterWidget::registerUser() {
    QString login = ui->loginLineEdit->text();
    QString nickname = ui->nicknameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    authManager->registerUser(nickname, login, password);
}

RegisterWidget::~RegisterWidget() {
    delete ui;
}
