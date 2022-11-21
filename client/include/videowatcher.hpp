#ifndef INC_2022_2_CASH_MAP_VIDEOWATCHER_HPP
#define INC_2022_2_CASH_MAP_VIDEOWATCHER_HPP

#include <string>

#include "event.hpp"

class IVideoWatcherController {
 public:
    virtual Event initialize() = 0;
    virtual Event play() = 0;
    virtual Event pause() = 0;
    virtual Event SetQuality(std::string quality) = 0;
    virtual Event setVolume(unsigned volume) = 0;
    virtual Event setSpeed(float speed) = 0;
    virtual Event setCurrentTime(uint64_t time) = 0;
    virtual Event toggleFullscreen() = 0;
    virtual Event setContentPath(std::string path) = 0;
    virtual ~IVideoWatcherController() = 0;
};

class IVideoWatcherView {
 public:
    virtual std::vector<float> getSpeedOptions();
    virtual uint64_t getDuration() = 0;
    virtual std::vector<std::string> getQualityOptions() = 0;
    virtual uint64_t getCurrentTime() = 0;
    virtual ~IVideoWatcherView() = 0;
};

class IVideoWatcher : IVideoWatcherController, IVideoWatcherView {
 public:
    virtual ~IVideoWatcher() = 0;
};

#endif //INC_2022_2_CASH_MAP_VIDEOWATCHER_HPP
