#include "include/UI/LoadingWidget.h"
#include "ui_loadingwidget.h"

LoadingWidget::LoadingWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LoadingWidget) {
    ui->setupUi(this);
}

LoadingWidget::~LoadingWidget() {
    delete ui;
}
