#include "RegistrationWidget.h"
#include "ui_registrationwidget.h"

RegistrationWidget::RegistrationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWidget)
{
    ui->setupUi(this);
}

RegistrationWidget::~RegistrationWidget()
{
    delete ui;
}
