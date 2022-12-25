#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videowatcher.h"

#include <QGridLayout>
#include <QWebEngineView>
#include <QtWebEngineWidgets>
#include <cassert>
#include <iostream>

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

    connect(view, &QWebEngineView::loadFinished, this, &MainWindow::LoadFinished);

    QString raw_link = "https://www.youtube.com/watch?v=_r0vlyp33pw";
    QString video_id = YoutubeWatcher::getVideoIdByRawLink(raw_link);
    QString url = YoutubeWatcher::getLinkByVideoId(video_id);
    std::cerr << url.toStdString();

    PlayerState initialState = watcher->getState();
    assert(initialState.playing == false);
    assert(initialState.content_url == "");
    assert(initialState.speed == 1.0);
    assert(initialState.timestamp == 0);

    watcher->setContentPath(url);
}

void MainWindow::LoadFinished() {
    std::cerr << "\n\nLOAD FINISHED\n\n";
    for (size_t i = 0; i < 10000; ++i)
        watcher->getCurrentSpeed();
}

MainWindow::~MainWindow()
{
    delete ui;
}
