#include <QtWebEngineWidgets>

#include "videowatcher.h"

YoutubeWatcher::YoutubeWatcher(QWebEngineView *_view) : view(_view) {
    view->setWindowTitle("Watch Up Youtube player");
    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);
    view->settings()->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    view->settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
}

void YoutubeWatcher::togglePlay() {
    QString js = "var video = document.querySelector('video'); if (video.paused) {video.play(); document.getElementById('movie_player').playVideo();} else {video.pause();}";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void YoutubeWatcher::setCurrentTime(double time) {
    QString js = "document.getElementById('movie_player').seekTo(" + QString::number(time) + ", true);";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void YoutubeWatcher::setCurrentSpeed(double time) {
    QString js = "document.querySelector('video').playbackRate = " + QString::number(time) + ";";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void YoutubeWatcher::setContentPath(const QString &path) {
    QString path1 = "https://www.youtube.com/embed/TodEc77i4t4?&enablejsapi=1&html5=1&controls=0";
    view->setUrl(QUrl(path1));
}

bool YoutubeWatcher::isPlaying() const {
    QString js = "document.querySelector('video').paused;";
    QString onPause = "";
    view->page()->runJavaScript(js, [&onPause](const QVariant &v){
        qDebug() << v.toString();
        onPause = v.toString();
    });
    while (onPause == "") {
        QApplication::processEvents();
    }
    return onPause == "false";
}

double YoutubeWatcher::getCurrentTime() const {
    QString js = "document.getElementById('movie_player').getCurrentTime();";
    double answer = -1;
    view->page()->runJavaScript(js, [&answer](const QVariant &v){
        qDebug() << v.toString();
        answer = v.toDouble();
    });
    while (answer == -1)
    {
        QApplication::processEvents();
    }
    return answer;
}

double YoutubeWatcher::getCurrentSpeed() const {
    QString js = "document.querySelector('video').playbackRate;";
    double answer = -1;
    view->page()->runJavaScript(js, [&answer](const QVariant &v){
        qDebug() << v.toString();
        answer = v.toDouble();
    });
    while (answer == -1)
    {
        QApplication::processEvents();
    }
    return answer;
}

QString YoutubeWatcher::getContentPath() const {
    return view->url().toString();
}

PlayerState YoutubeWatcher::getState() const {
    PlayerState result = {
        .playing = isPlaying(),
        .content_url = getContentPath(),
        .speed = getCurrentSpeed(),
        .timestamp = getCurrentTime()
    };
    return result;
}

static QString getLinkByVideoId(const QString& id) {
    return "https://www.youtube.com/embed/" + id + "?&enablejsapi=1&html5=1&controls=0";
}
