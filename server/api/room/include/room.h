#ifndef WATCH_UP_PROJECT_ROOM_H
#define WATCH_UP_PROJECT_ROOM_H

#include <vector>
#include <memory>

#include <boost/beast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/functional/hash.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio/deadline_timer.hpp>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;
using uuid = boost::uuids::uuid;


class IViewer;
class shared_state;

typedef std::weak_ptr<IViewer> w_viewer_ptr;
typedef std::shared_ptr<IViewer> viewer_ptr;
typedef std::shared_ptr<shared_state> state_ptr;


class IRoom {
public:
    virtual     ~IRoom()              = default;
    virtual void join (w_viewer_ptr)  = 0;
    virtual void leave(uuid id)       = 0;
    virtual void check_timings()      = 0;
    virtual void pause()              = 0;
    virtual void play()               = 0;
    virtual void synchronize()        = 0;
    virtual void set_resource(const std::string&)       = 0;
    virtual void set_nickname(const uuid& viewer, std::string&& nick) = 0;
    virtual void send_chat_msg(uuid viewer, const std::string& msg) = 0;

    virtual w_viewer_ptr get_viewer(const uuid& ) = 0;
    virtual const uuid get_id() const = 0;
};


class Room: public IRoom, public std::enable_shared_from_this<Room>{
public:
    Room(w_host_ptr host, uuid id, state_ptr state);
    ~Room()        override;
    void start();
    void join (w_viewer_ptr) override;
    void leave(uuid id)    override;
    void check_timings()   override;
    void pause()           override;
    void play()            override;
    void synchronize()     override;
    void send_chat_msg(uuid viewer, const std::string& msg) override;
    void set_resource(const std::string&) override;

    void start_timer();
    void stop_timer();

    const uuid get_id() const override;
    w_viewer_ptr get_viewer(const uuid& ) override;

private:
    bool playing;
    uuid id_;
    w_host_ptr host_;
    state_ptr state_;
    boost::asio::deadline_timer check_timer_;
    std::unordered_map<uuid, w_viewer_ptr, boost::hash<uuid>> participants_;
};

#endif //WATCH_UP_PROJECT_ROOM_H
