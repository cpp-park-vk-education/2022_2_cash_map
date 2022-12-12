#ifndef WATCH_UP_PROJECT_SERVER_HPP
#define WATCH_UP_PROJECT_SERVER_HPP

#include <string>

struct Options{
    std::string ip;
    unsigned short port;
};

class Server{
public:
    Server();
    Server(const Options& opts);
    void run();
    void stop();

private:
    bool started;
    Options opts_;
};
#endif //WATCH_UP_PROJECT_SERVER_HPP
