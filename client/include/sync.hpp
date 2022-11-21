#ifndef WATCH_UP_PROJECT_SYNC_HPP
#define WATCH_UP_PROJECT_SYNC_HPP

#include "videowatcher.hpp"
#include "auth.hpp"

class ISyncer {
 private:
    IVideoWatcher* watcher;
    Session* session;
 public:
    int64_t getDifference();
    void sync();
};

class HostSyncer : ISyncer {};
class HostageSyncer : ISyncer {};

#endif //WATCH_UP_PROJECT_SYNC_HPP
