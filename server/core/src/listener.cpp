#include "listener.h"

#include <memory>

#include <boost/beast/core.hpp>

#include "ws_session.hpp"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;


listener::listener(net::io_context &ioc, tcp::endpoint&& endpoint):
        state_(std::make_shared<shared_state>(ioc)), ioc_(ioc), acceptor_(ioc), socket_(ioc)
{
    error_code ec;
    acceptor_.open(endpoint.protocol(), ec);
    if(ec){
        std::cout << "[acceptor open error] " << ec.message() << std::endl;
    }
    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if (ec){
        std::cout << "[acceptor set_option error] " << ec.message() << std::endl;
    }
    acceptor_.bind(endpoint, ec);
    if(ec){
        std::cout << "[acceptor bind error] " << ec.message() << std::endl;
    }
    acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
    if(ec){
        std::cout << "[acceptor listen error] " << ec.message() << std::endl;
    }
    //TODO remove
    std::cout << endpoint.address().to_string() << std::endl;
}


void listener::async_accept() {
    acceptor_.async_accept(socket_, [self{shared_from_this()}](error_code ec){
        //TODO check for ec
        //TODO log
        if(ec){
            std::cout <<"[listener async_accept error] " << ec.message() << std::endl;
        }

        std::cout << "[connection accepted]" << std::endl;
        self->on_accept(ec);
    });
}


void listener::on_accept(error_code& ec) {
    // TODO check ec
    if(ec){
        std::cout << "[on accept error] "<< ec.message() << std::endl;
    }

    std::make_shared<ws_session>(std::move(socket_), state_)->run();
    async_accept();
}

listener::~listener() {
    acceptor_.close();
}

