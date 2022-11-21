#ifndef WATCH_UP_PROJECT_ROOM_H
#define WATCH_UP_PROJECT_ROOM_H

#include <vector>
#include <memory>

#include "viewer.h"

typedef std::weak_ptr<IViewer> w_viewer_ptr;
typedef std::shared_ptr<IViewer> viewer_ptr;

class IRoom {
public:
    virtual     ~IRoom()          = 0;
    virtual void join (viewer_ptr)= 0;
    virtual void leave(viewer_ptr)= 0;
    virtual void check_timings()  = 0;
    virtual void pause()          = 0;
    virtual void play()           = 0;
    virtual void synchronize()    = 0;

};


class Room: public IRoom{
public:
    void join (viewer_ptr) override;
    void leave(viewer_ptr) override;
    void check_timings()   override;
    void pause()           override;
    void play()            override;
    void synchronize()     override;
private:
    std::vector<w_viewer_ptr> members_; //TODO choose container
};

#endif //WATCH_UP_PROJECT_ROOM_H
