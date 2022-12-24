#include "include/UI/ChatMessageWidget.h"
#include "ui_chatmessagewidget.h"

ChatMessageWidget::ChatMessageWidget(const QString &sender, const QString &message, const QString &time, QWidget *parent) : QWidget(parent),
                                                                                                                            ui(new Ui::ChatMessageWidget) {
    ui->setupUi(this);
    ui->timeLabel->setText(time);
    ui->senderLabel->setText(sender);
    ui->textBrowser->setText(message);
}

ChatMessageWidget::~ChatMessageWidget()
{
    delete ui;
}
