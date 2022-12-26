#include "include/UI/RutubeWatcher.h"
#include <QApplication>
#include <QWebEngineSettings>


RutubeWatcher::RutubeWatcher(QWebEngineView *_view) : view(_view), urlWasSetted(false) {
    view->setWindowTitle("Watch Up Rutube player");
    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);
    view->settings()->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    view->settings()->setAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript, true);
    view->settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
    view->settings()->setAttribute(QWebEngineSettings::HyperlinkAuditingEnabled, false);
    view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);

    webPage = new QWebEnginePage();
    view->setPage(webPage);

    QObject::connect(view, &QWebEngineView::loadProgress, this, &RutubeWatcher::handleLoading);
}

RutubeWatcher::RutubeWatcher(IVideoWatcher &&watcher) {
//    this->view = watcher.getView();
//    watcher.setView(nullptr);
//    this->webPage = watcher.getWebPage();
//    watcher.setWebPage(nullptr);
//    urlWasSetted = false;
//    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
//    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
//    view->settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);
//    view->settings()->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);
//    view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
//    view->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
//    view->settings()->setAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript, true);
//    view->settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
//    view->settings()->setAttribute(QWebEngineSettings::HyperlinkAuditingEnabled, false);
//    view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
//    view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);

//    QObject::connect(view, &QWebEngineView::loadProgress, this, &RutubeWatcher::handleLoading);
}

void RutubeWatcher::handleLoading(int loaded_percent) {
    if (loaded_percent == 100) {
        qDebug() << "READY TO WATCH!";
        emit ReadyToWatch(true);
        initPlayerAfterSetContent();
    }
}

void RutubeWatcher::initPlayerAfterSetContent() {
    QString js = "function removeAdverts() { var i = 0; var timer_id = setInterval(function() { console.log(i); if (i == 4) { clearInterval(timer_id); return;} i++; try { var ads = document.getElementsByClassName('raichu-advert-module__SDKWrapper___1-DyI'); for (let i = 0; i < ads.length; ++i) { console.log(ads[i].childElementCount); if (ads[i].childElementCount > 2) {ads[i].remove();} }} catch (error) { console.log(error);}} , 2000);}var is_playing = false;var current_time = 0.0;var current_speed = 1.0;window.addEventListener('message', function (event) { var message = JSON.parse(event.data); console.log(message.type); switch (message.type) { case 'player:changeState': is_playing = message.data.state == 'playing'; break; case 'player:currentTime': current_time = message.data.time; break; case 'player:rollState': if (message.data.state == 'play') { removeAdverts(); } break; };});";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void RutubeWatcher::removeAdverts() {
    QString js = "var i = 0; var timer_id = setInterval(function() { console.log(i); if (i == 4) { clearInterval(timer_id); return;} i++; try { var ads = document.getElementsByClassName('raichu-advert-module__SDKWrapper___1-DyI'); for (let i = 0; i < ads.length; ++i) { console.log(ads[i].childElementCount); if (ads[i].childElementCount > 2) {ads[i].remove();} }} catch (error) { console.log(error);}} , 2000);";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void RutubeWatcher::togglePlay() {
    if (!urlWasSetted)
        throw std::runtime_error("Can't operate with Rutube Watcher before setting url of video");
    QString js = "var command = is_playing ? { type: 'player:pause', data: {}} : { type: 'player:play', data: {}};window.postMessage(JSON.stringify(command), '*');";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void RutubeWatcher::setCurrentTime(double time) {
    if (!urlWasSetted)
        throw std::runtime_error("Can't operate with Rutube Watcher before setting url of video");
    QString js = "window.postMessage(JSON.stringify({type: 'player:setCurrentTime', data: { time: " + QString::number(time) + " }}), '*');";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

void RutubeWatcher::setCurrentSpeed(double speed) {
    if (!urlWasSetted)
        throw std::runtime_error("Can't operate with Rutube Watcher before setting url of video");
    return;
}

void RutubeWatcher::setContentPath(const QString &path) {
    urlWasSetted = true;
    qDebug() << "urlWasSetted: true\n" << path;
    QString js = "var window = open(\"" + path + "\",\"_self\")";
    view->page()->runJavaScript(js, [](const QVariant &v){ qDebug() << v.toString(); });
}

bool RutubeWatcher::isPlaying() const {
    if (!urlWasSetted)
        return false;
    QString js = "is_playing";
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

double RutubeWatcher::getCurrentTime() const {
    if (!urlWasSetted)
        return 0.0;
    QString js = "current_time";
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

double RutubeWatcher::getCurrentSpeed() const {
    if (!urlWasSetted)
        return 1.0;
    QString js = "current_speed";
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

QString RutubeWatcher::getContentPath() const {
    if (!urlWasSetted)
        return "";
    return view->url().toString();
}

PlayerState RutubeWatcher::getState() const {
    return {
        isPlaying(),
        getContentPath(),
        getCurrentSpeed(),
        getCurrentTime()
    };
}

QString RutubeWatcher::getLinkByVideoId(const QString& id) {
    return "https://rutube.ru/play/embed/" + id;
}

QString RutubeWatcher::getVideoIdByRawLink(const QUrl& url) {
    auto parts_of_url = url.toString().split("video/");
    if (parts_of_url.size() < 2)
        throw std::runtime_error("bad rutube video url.");
    return parts_of_url.at(1);
}

QWebEngineView *RutubeWatcher::getView() {
    return view;
}

void RutubeWatcher::setView(QWebEngineView *view) {
    this->view = view;
}

QWebEnginePage *RutubeWatcher::getWebPage() {
    return webPage;
}

void RutubeWatcher::setWebPage(QWebEnginePage *view) {
    webPage = view;
}

RutubeWatcher::~RutubeWatcher() {
    delete view;
    delete webPage;
}
