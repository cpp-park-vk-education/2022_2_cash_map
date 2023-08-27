#include "include/UI/LoadingWidget.h"
#include "ui_loadingwidget.h"

#include <QMovie>

LoadingWidget::LoadingWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LoadingWidget) {
    ui->setupUi(this);
    movie = new QMovie(":resources/icons/loading.gif");
    ui->label->setMovie(movie);
    ui->label->setScaledContents(true);
    movie->start();
}

LoadingWidget::~LoadingWidget() {
    delete ui;
    delete movie;
}
