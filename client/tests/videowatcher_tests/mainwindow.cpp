#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videowatcher.h"

#include <QGridLayout>
#include <QWebEngineView>
#include <QtWebEngineWidgets>
#include <cassert>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), watcher(nullptr)
{
    ui->setupUi(this);
    QWidget *wgt = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(wgt);
    ui->centralwidget->setLayout(gridLayout);
    wgt->setLayout(gridLayout);

    wgt->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
                                          "border-radius: 25px;background-color:black;"));
    ui->centralwidget->layout()->addWidget(wgt);

    QWebEngineView *view = new QWebEngineView(wgt);
    wgt->layout()->addWidget(view);
    watcher = new YoutubeWatcher(view);

    QString url = YoutubeWatcher::getLinkByVideoId("TE2tfavlo3E&t");
    assert(url != "");

    PlayerState initialState = watcher->getState();
    assert(initialState.playing == false);
    assert(initialState.content_url == "");
}

MainWindow::~MainWindow()
{
    delete ui;
}
