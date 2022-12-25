#ifndef YOUTUBEWATCHER_H
#define YOUTUBEWATCHER_H

#include "include/UI/CustomWebView.h"
#include <QtWebEngineWidgets/QWebEngineView>
#include <QObject>
#include <iostream>


// Означает текущее состояние плеера
struct PlayerState {
    bool playing = false;
    QString content_url = "";
    double speed = 1.0;
    double timestamp = 0;
};

class IVideoWatcher : public QObject {
    Q_OBJECT
 public:
    virtual ~IVideoWatcher() = default;
    /// @brief Переключает режимы PLAY / PAUSE видео
    virtual void togglePlay() = 0;
    /// @brief Устанавливает время плеера
    /// @param time время плеера
    virtual void setCurrentTime(double time) = 0;
    /// @brief Устанавливает скорость воспроизведения видео
    /// @param speed скорость воспроизведения
    virtual void setCurrentSpeed(double speed) = 0;
    /// @brief Устанавливает путь до видеоконтента
    /// @param path путь до видеоконтента
    virtual void setContentPath(const QString& path) = 0;

    /// @brief Играет ли в данный момент видео
    /// @return true - играет, false - нет
    virtual bool isPlaying() const = 0;
    /// @brief Получить текущее время плеера
    /// @return текущее время плеера
    virtual double getCurrentTime() const = 0;
    /// @brief Получить текущую скокрость воспроизведения видео
    /// @return текущая скорость воспроизведения видео
    virtual double getCurrentSpeed() const = 0;
    /// @brief Получить текущий путь до видеоконтента
    /// @return путь до видеоконтента
    virtual QString getContentPath() const = 0;

    /// @brief Получить текущее состояние плеера
    /// @return текущее состояние плеера
    virtual PlayerState getState() const = 0;

    virtual QString getLinkByVideoId(const QString& id) = 0;

    virtual QString getVideoIdByRawLink(const QUrl& url) = 0;

signals:
    void ReadyToWatch(bool ok);
};

class YoutubeWatcher : public IVideoWatcher {
private:
    void handleLoading(int progress_percent);
public:
    explicit YoutubeWatcher(CustomWebView *_view);
    ~YoutubeWatcher() = default;
    /// @brief Переключает режимы PLAY / PAUSE видео
    virtual void togglePlay() override;
    /// @brief Устанавливает время плеера
    /// @param time время плеера
    virtual void setCurrentTime(double time) override;
    /// @brief Устанавливает скорость воспроизведения видео
    /// @param speed скорость воспроизведения
    virtual void setCurrentSpeed(double speed) override;
    /// @brief Устанавливает путь до видеоконтента
    /// @param path путь до видеоконтента
    virtual void setContentPath(const QString& path) override;

    /// @brief Играет ли в данный момент видео
    /// @return true - играет, false - нет
    virtual bool isPlaying() const override;
    /// @brief Получить текущее время плеера
    /// @return текущее время плеера
    virtual double getCurrentTime() const override;
    /// @brief Получить текущую скокрость воспроизведения видео
    /// @return текущая скорость воспроизведения видео
    virtual double getCurrentSpeed() const override;
    /// @brief Получить текущий путь до видеоконтента
    /// @return путь до видеоконтента
    virtual QString getContentPath() const override;

    /// @brief Получить текущее состояние плеера
    /// @return текущее состояние плеера
    virtual PlayerState getState() const override;

    /// @brief Получить ссылку для задания пути до видеоконтента
    /// @param id id ютубовского видео
    /// @return возвращает готовую ссылку, которую можно передавать в setContentPath
    virtual QString getLinkByVideoId(const QString& id) override;

    virtual QString getVideoIdByRawLink(const QUrl& url) override;

private:
    bool urlWasSetted = false;
    CustomWebView *view;
};



#endif // YOUTUBEWATCHER_H
