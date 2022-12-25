#include "videowatcher.h"


void YoutubeWatcher::handleLoading(int loaded_percent) {
    if (loaded_percent == 100) {
        qDebug() << "READY TO WATCH!";
        emit ReadyToWatch(true);
        togglePlay();
    }
}

YoutubeWatcher::YoutubeWatcher(QWebEngineView *_view) : view(_view), urlWasSetted(false) {
    view->setWindowTitle("Watch Up Youtube player");
    view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);
    view->settings()->setAttribute(QWebEngineSettings::SpatialNavigationEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    view->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
    view->settings()->setAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript, true);
    view->settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
    view->settings()->setAttribute(QWebEngineSettings::HyperlinkAuditingEnabled, false);

    QWebEnginePage *webPage = new QWebEnginePage();
    view->setPage(webPage);

    QObject::connect(view, &QWebEngineView::loadProgress, this, &YoutubeWatcher::handleLoading);
}

void YoutubeWatcher::togglePlay() {
    if (!urlWasSetted)
        throw std::runtime_error("Can't operate with Youtube Watcher before setting url of video");
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

RutubeWatcher::RutubeWatcher(QWebEngineView *_view) : view(_view), urlWasSetted(false) {
    view->setWindowTitle("Watch Up Youtube player");
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

    QWebEnginePage *webPage = new QWebEnginePage();
    view->setPage(webPage);

    QObject::connect(view, &QWebEngineView::loadProgress, this, &RutubeWatcher::handleLoading);
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
    qDebug() << "urlWasSetted: true\n";
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
