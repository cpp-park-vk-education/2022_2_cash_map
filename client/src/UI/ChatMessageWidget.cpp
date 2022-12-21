#include "ChatMessageWidget.h"
#include "ui_chatmessagewidget.h"

ChatMessageWidget::ChatMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageWidget)
{
    ui->setupUi(this);
}

ChatMessageWidget::~ChatMessageWidget()
{
    delete ui;
}
