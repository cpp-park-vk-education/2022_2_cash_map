#ifndef VIDEOWATCHER_H
#define VIDEOWATCHER_H

#include <QObject>

#include <QtWebEngineWidgets>
#include <iostream>

struct PlayerState {
    bool playing = false;
    QString content_url = "";
    double speed = 1.0;
    double timestamp = 0;

    PlayerState() = default;
};

class IVideoWatcher : public QObject {
    Q_OBJECT
 public:
    virtual void togglePlay() = 0;
    virtual void setCurrentTime(double time) = 0;
    virtual void setCurrentSpeed(double speed) = 0;
    virtual void setContentPath(const QString& path) = 0;

    virtual bool isPlaying() const = 0;
    virtual double getCurrentTime() const = 0;
    virtual double getCurrentSpeed() const = 0;
    virtual QString getContentPath() const = 0;

    virtual PlayerState getState() const = 0;

signals:
    void ReadyToWatch(bool ok);

};

class YoutubeWatcher : public IVideoWatcher {
    Q_OBJECT
private:
    void handleLoading(int loaded_percent);
public:
    YoutubeWatcher() = delete;

    explicit YoutubeWatcher(QWebEngineView *_view);
    void togglePlay() override;
    void setCurrentTime(double time) override;
    void setCurrentSpeed(double speed) override;
    void setContentPath(const QString& path) override;

    bool isPlaying() const override;
    double getCurrentTime() const override;
    double getCurrentSpeed() const override;
    QString getContentPath() const override;

    PlayerState getState() const override;

    static QString getLinkByVideoId(const QString& id);
    static QString getVideoIdByRawLink(const QUrl& url);

private:
    QWebEngineView *view = nullptr;
    bool urlWasSetted = false;
};

class RutubeWatcher : public IVideoWatcher {
    Q_OBJECT
private:
    void handleLoading(int loaded_percent);
    void removeAdverts();
    void initPlayerAfterSetContent();
public:
    RutubeWatcher() = delete;

    explicit RutubeWatcher(QWebEngineView *_view);
    void togglePlay() override;
    void setCurrentTime(double time) override;
    void setCurrentSpeed(double speed) override;
    void setContentPath(const QString& path) override;

    bool isPlaying() const override;
    double getCurrentTime() const override;
    double getCurrentSpeed() const override;
    QString getContentPath() const override;

    PlayerState getState() const override;

    static QString getLinkByVideoId(const QString& id);
    static QString getVideoIdByRawLink(const QUrl& url);

private:
    QWebEngineView *view = nullptr;
    bool urlWasSetted = false;
};


#endif // VIDEOWATCHER_H
