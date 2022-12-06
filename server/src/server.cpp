#include "server.h"

#include <iostream>
#include <memory>

#include <boost/asio/ip/tcp.hpp>

#include "listener.h"


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;

Server::Server(): started(false), opts_({"127.0.0.1", 8080})
{}

void Server::run() {
    std::cout << "Server run" << std::endl;
    net::io_context ioc;

    tcp::endpoint endpoint{{net::ip::make_address(opts_.ip)}, opts_.port};


    std::make_shared<listener>(ioc, std::move(endpoint))->async_accept();

    ioc.run();
    started = true;
}
