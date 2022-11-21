#include "include/UI/LoginWidget.h"
#include "ui_startwidget.h"

StartWidget::StartWidget(QWidget *parent) : QWidget(parent), ui(new Ui::StartWidget) {
    ui->setupUi(this);
}

StartWidget::~StartWidget() {
    delete ui;
}
