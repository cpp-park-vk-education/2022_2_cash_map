#ifndef WATCH_UP_PROJECT_EVENT_HPP
#define WATCH_UP_PROJECT_EVENT_HPP

#include <vector>
#include <string>
#

#include "auth.hpp"

class Event {
 public:
    enum Events { INITIALIZE, PLAY, PAUSE, SET_QUALITY, SET_VOLUME,
                  SET_SPEED, SET_CURRENT_TIME, TOGGLE_FULLSCREEN,
                  SET_CONTENT_PATH
    };
    Event(Events _eventType, std::unordered_map<std::string, std::string> _context);
    Events getEventType();
    std::unordered_map<std::string, std::string> getContext();
 private:
    Events eventType;
    std::unordered_map<std::string, std::string> context;
};

class EventSerializer {
 public:
    static std::string Serialize(Event event);
    static Event Deserialize(std::string str);
};

class EventHandler {
 private:
    Session* session;
    EventSerializer eventSerializer;
 public:
    void sendEvent(Event event);
    Event getEvent();
};

#endif //WATCH_UP_PROJECT_EVENT_HPP
