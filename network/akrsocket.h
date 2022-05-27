#include <stdio.h>
#include <stdlib.h>
#include <cinttypes>
#include <sys/socket.h>
#include <sys/types.h>
#include <memory>
#include "spdlog/spdlog.h"

constexpr int SOCKET_DEFAULT_PORT = 25623;

char buffer[1025]; // data buffer of 1K

// set of socket descriptors
fd_set readfds;

enum class socket_mode_t
{
    UNSET,
    CLIENT,
    SERVER
};

enum class socket_type_t
{
    TCP,
    UDP
};

enum class socket_status_t
{
    UNSET = -1,
    INIT = 0,
    BINDED = 1,
    ERROR = 2,
    CLOSED = 3
};

class akrsocket_serv_t
{
    int port;
    socklen_t address_len;
    int sockfd;
    socket_mode_t socket_mode = socket_mode_t::UNSET;
    socket_status_t socket_status = socket_status_t::UNSET;

    void initialize(int domain, int type, int protocol, int port)
    {
        spdlog::trace("akrsocket_serv_t::initialize()");

        this->port = port; // The port you want to use
        this->address_len = sizeof(struct sockaddr);
        this->sockfd = socket(domain, type, protocol);
        this->socket_mode = socket_mode_t::SERVER;
        this->socket_status = socket_status_t::INIT;

        if (this->sockfd < 0)
        {
            spdlog::error("akrsocket_serv_t::initialize() - socket() failed");
        }
    }

    void initialize(int domain, int type, int protocol)
    {
        this->initialize(domain, type, protocol, SOCKET_DEFAULT_PORT);
    }

    int bind(const struct sockaddr *addr, socklen_t addlen)
    {
        spdlog::trace("akrsocket_serv_t::bind()");
        if (this->socket_status == socket_status_t::INIT)
        {
            if (::bind(this->sockfd, addr, addlen) == 0)
            {
                spdlog::trace("akrsocket_serv_t::bind() - binded");
                this->socket_status = socket_status_t::BINDED;
                return 0;
            }
            else
            {
                spdlog::trace("akrsocket_serv_t::bind() - bind error");
                this->socket_status = socket_status_t::ERROR;
                return -1;
            }
        }
        else
        {
            return -1;
        }
    }
};