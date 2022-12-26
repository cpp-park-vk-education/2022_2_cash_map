#ifndef RUTUBEWATCHER_H
#define RUTUBEWATCHER_H

#include <QtWebEngineWidgets/QWebEngineView>
#include "YoutubeWatcher.h"

class RutubeWatcher : public IVideoWatcher {
    Q_OBJECT
private:
    void handleLoading(int loaded_percent);
    void removeAdverts();
    void initPlayerAfterSetContent();
public:
    explicit RutubeWatcher(QWebEngineView *_view);
    RutubeWatcher(IVideoWatcher &&watcher);
    ~RutubeWatcher();
    void togglePlay() override;
    void setCurrentTime(double time) override;
    void setCurrentSpeed(double speed) override;
    void setContentPath(const QString& path) override;

    bool isPlaying() const override;
    double getCurrentTime() const override;
    double getCurrentSpeed() const override;
    QString getContentPath() const override;

    PlayerState getState() const override;

    QString getLinkByVideoId(const QString& id) override;
    QString getVideoIdByRawLink(const QUrl& url) override;

    QWebEngineView *getView() override;
    void setView(QWebEngineView *view) override;

    QWebEnginePage *getWebPage() override;

    void setWebPage(QWebEnginePage *view) override;
private:
    QWebEngineView *view = nullptr;
    bool urlWasSetted = false;
    QWebEnginePage *webPage;
};

#endif // RUTUBEWATCHER_H
