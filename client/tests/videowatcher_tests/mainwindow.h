#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class YoutubeWatcher;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void LoadFinished();

private:
    Ui::MainWindow *ui;
    YoutubeWatcher *watcher;
};
#endif // MAINWINDOW_H
