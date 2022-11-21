#ifndef WATCH_UP_PROJECT_VIEWER_H
#define WATCH_UP_PROJECT_VIEWER_H

#include <string>
#include <memory>

#include "room.h"
#include "chat.h"


typedef std::shared_ptr<IRoom> room_ptr;
typedef std::shared_ptr<IChat> chat_ptr;

struct Access_options{
    bool can_pause;
    bool can_rewind;
};


class IViewer {
public:
    virtual ~IViewer();
    virtual void pause()                             =0;
    virtual void play()                              =0;
    virtual void rewind(int offset)                  =0;
    virtual std::string get_nickname()               =0;
    virtual void set_nickname(std::string)           =0;
    virtual void send_chat_msg(std::string msg)      =0;
    virtual void set_access_opts(Access_options opts)=0;
};

class Viewer: public IViewer{
public:
    void pause()                             override;
    void play()                              override;
    void rewind(int offset)                  override;
    std::string get_nickname()               override;
    void set_nickname(std::string)           override;
    void send_chat_msg(std::string msg)      override;
    void set_access_opts(Access_options opts)override;
protected:
    room_ptr room_;
    chat_ptr chat_;

};

class Host: public Viewer{
public:
    void synchronize();
    void change_access_opts();
};

#endif //WATCH_UP_PROJECT_VIEWER_H


