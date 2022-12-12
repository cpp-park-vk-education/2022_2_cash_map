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
    virtual     ~IRoom()                                             = default;

    virtual void start()                                             = 0;
    virtual void join (w_viewer_ptr)                                 = 0;
    virtual void leave(const uuid& id, const std::string& nick)      = 0;

    virtual void ping()                                              = 0;
    virtual void pause(const boost::posix_time::time_duration &)     = 0;
    virtual void play()                                              = 0;
    virtual void synchronize(const boost::posix_time::time_duration &)= 0;

    virtual void set_resource(const std::string&)                    = 0;
    virtual void send_chat_msg(uuid viewer, const std::string& msg)  = 0;
    virtual void set_nickname(const uuid& viewer, std::string&& nick)= 0;

    virtual w_viewer_ptr get_viewer(const uuid& )                    = 0;
    virtual const uuid get_id() const                                = 0;


    virtual void start_timer()                                       = 0;
    virtual void stop_timer()                                        = 0;
    virtual void on_pong(std::unordered_map<std::string, std::string> &req) =0;

};


class Room: public IRoom, public std::enable_shared_from_this<Room>{
public:
    Room(uuid&& host, uuid&& id, state_ptr state);
    ~Room()                                                  override;
    void start()                                             override;
    void join (w_viewer_ptr)                                 override;
    void leave(const uuid& id, const std::string& nick)      override;
    void ping()                                              override;
    void pause(const boost::posix_time::time_duration &)     override;
    void play()                                              override;
    void synchronize(const boost::posix_time::time_duration&)override;
    void send_chat_msg(uuid viewer, const std::string& msg)  override;
    void set_resource(const std::string&)                    override;
    void set_nickname(const uuid& viewer, std::string&& nick)override;

    void start_timer()                                       override;
    void stop_timer()                                        override;

    const uuid get_id() const                                override;
    w_viewer_ptr get_viewer(const uuid& )                    override;
    void on_pong(std::unordered_map<std::string, std::string> &req) override;

private:
    struct ping_info{
        boost::posix_time::time_duration player_time;
        boost::posix_time::time_duration latency;
        boost::posix_time::ptime response;
        uuid viewer_id;
    };
    bool playing;
    uuid id_;
    uuid host_;
    state_ptr state_;
    boost::asio::deadline_timer check_timer_;
   // boost::asio::deadline_timer ping_timeout;
    std::unordered_map<uuid, w_viewer_ptr, boost::hash<uuid>> participants_;
    std::vector<std::pair<uuid, std::string>> viewers_;
    std::pair<boost::posix_time::ptime, std::vector<ping_info>> ping_;
    std::string src_;

};

#endif //WATCH_UP_PROJECT_ROOM_H
