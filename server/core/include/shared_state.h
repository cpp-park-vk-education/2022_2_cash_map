#ifndef WATCH_UP_PROJECT_SHARED_STATE_H
#define WATCH_UP_PROJECT_SHARED_STATE_H

#include <memory>
#include <unordered_map>

#include <boost/beast/core.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/functional/hash.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

class IRoom;

typedef std::shared_ptr<IRoom> room_ptr;
typedef std::weak_ptr<IRoom> w_room_ptr;
typedef boost::uuids::uuid uuid;

class shared_state: public std::enable_shared_from_this<shared_state>{
public:
    explicit shared_state(net::io_context &ioc);
    void add_room(const uuid &room_id, w_room_ptr&& room);
    void remove_room(uuid room_id);
    w_room_ptr get_room(uuid room_id);
    net::io_context &get_io_context() const;
private:
    std::unordered_map<uuid, w_room_ptr, boost::hash<uuid>> rooms_;
    net::io_context &ioc_;
};



#endif //WATCH_UP_PROJECT_SHARED_STATE_H
