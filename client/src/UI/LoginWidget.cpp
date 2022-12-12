#include "include/UI/LoginWidget.h"
#include "ui_startwidget.h"

StartWidget::StartWidget(AuthorizationManager *authManager, QWidget *parent) : QWidget(parent),
                                                                               ui(new Ui::StartWidget),
                                                                               authManager(authManager) {
    ui->setupUi(this);

    connect(ui->enterButton, SIGNAL(clicked()), this, SLOT(authTry()));
}

void StartWidget::authTry() {
    QString login = ui->loginLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    AuthenticationStatus response = authManager->authenticateUser(login, password);
    if (response == Success) {
        emit authorized();
    } else if (response == IncorrectLoginOrPassword) {
        ui->errorLabel->setText("Incorrect login or password");
    }
}

StartWidget::~StartWidget() {
    delete ui;
}
