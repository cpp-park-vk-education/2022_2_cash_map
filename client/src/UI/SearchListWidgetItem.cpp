#include "include/UI/SearchListWidgetItem.h"
#include "ui_SearchListWidgetItem.h"
#include <iostream>


SearchListWidgetItem::SearchListWidgetItem(QWidget *parent) : QWidget(parent), ui(new Ui::SearchListWidgetItem) {
    ui->setupUi(this);
}

SearchListWidgetItem::~SearchListWidgetItem()
{
    delete ui;
}


void SearchListWidgetItem::setHeaderText(const char *text) {
    ui->headerLabel->setText(QString(text));
    std::cout << ui->headerLabel->text().toStdString();
}

void SearchListWidgetItem::setPreviewImage(const char *bytes) {

}

void SearchListWidgetItem::setDescription(const char *text) {
    ui->descriptionLabel->setText(QString(text));
}

void SearchListWidgetItem::setVideoLink(const char *link) {

}
