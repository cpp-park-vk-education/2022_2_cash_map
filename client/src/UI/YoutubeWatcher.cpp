#include "include/UI/YoutubeWatcher.h"
#include "qurlquery.h"

#include <QApplication>
#include <QWebEngineSettings>


void YoutubeWatcher::handleLoading(int loaded_percent) {
    if (loaded_percent == 100) {
        qDebug() << "READY TO WATCH!";
        togglePlay();
        emit ReadyToWatch(true);
    }
}

YoutubeWatcher::YoutubeWatcher(QWebEngineView *_view) : urlWasSetted(false), view(_view) {
//    view->setWindowTitle("Watch Up Youtube player");
//    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
//    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
//    view->settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);
//    view->settings()->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);
//    view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
//    view->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
//    view->settings()->setAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript, true);
//    view->settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
//    view->settings()->setAttribute(QWebEngineSettings::HyperlinkAuditingEnabled, false);

//    webPage = new QWebEnginePage();
//    view->setPage(webPage);

//    QObject::connect(view, &QWebEngineView::loadProgress, this, &YoutubeWatcher::handleLoading);
}

YoutubeWatcher::YoutubeWatcher(IVideoWatcher &&watcher) {
    this->view = watcher.getView();
    watcher.setView(nullptr);
    this->webPage = watcher.getWebPage();
    watcher.setWebPage(nullptr);
    delete webPage;
    webPage = new QWebEnginePage();
    view->setPage(webPage);
    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);
    view->settings()->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    view->settings()->setAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript, true);
    view->settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
    view->settings()->setAttribute(QWebEngineSettings::HyperlinkAuditingEnabled, false);



    urlWasSetted = true;

    QObject::connect(view, &QWebEngineView::loadProgress, this, &YoutubeWatcher::handleLoading);
}

void YoutubeWatcher::togglePlay() {
    if (!urlWasSetted)
        throw std::runtime_error("Can't operate with Youtube Watcher before setting url of video");
    qDebug() << "PLAY";
    QString js = "document.getElementsByClassName('ytp-large-play-button')[0].click();";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void YoutubeWatcher::setCurrentTime(double time) {
    if (!urlWasSetted)
        throw std::runtime_error("Can't operate with Youtube Watcher before setting url of video");
    QString js = "document.getElementById('movie_player').seekTo(" + QString::number(time) + ", true);";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void YoutubeWatcher::setCurrentSpeed(double time) {
    if (!urlWasSetted)
        throw std::runtime_error("Can't operate with Youtube Watcher before setting url of video");
    QString js = "document.querySelector('video').playbackRate = " + QString::number(time) + ";";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void YoutubeWatcher::setContentPath(const QString &path) {
    urlWasSetted = true;
    view->setUrl(QUrl(path));
}

bool YoutubeWatcher::isPlaying() const {
    if (!urlWasSetted)
        return false;
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
    if (!urlWasSetted)
        return 0.0;
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
    if (!urlWasSetted)
        return 1.0;
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
    if (!urlWasSetted)
        return "";
    return view->url().toString();
}

PlayerState YoutubeWatcher::getState() const {
    return {
        isPlaying(),
        getContentPath(),
        getCurrentSpeed(),
        getCurrentTime()
    };
}

QString YoutubeWatcher::getLinkByVideoId(const QString& id) {
    return "https://www.youtube.com/embed/" + id + "?&enablejsapi=1&html5=1&controls=2&autoplay=1";
}

QString YoutubeWatcher::getVideoIdByRawLink(const QUrl& url) {
    QUrlQuery query(url);
    if (!query.hasQueryItem("v"))
        throw std::runtime_error("Wrong video link, doesn't have 'v' query parameter");

    return query.queryItemValue("v");
}

QWebEngineView *YoutubeWatcher::getView() {
    return view;
}

void YoutubeWatcher::setView(QWebEngineView *view) {
    this->view = view;
}

QWebEnginePage *YoutubeWatcher::getWebPage() {
    return webPage;
}

void YoutubeWatcher::setWebPage(QWebEnginePage *view) {
    webPage = view;
}


YoutubeWatcher::~YoutubeWatcher() {
    delete view;
    delete webPage;
}
