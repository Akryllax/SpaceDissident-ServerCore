/*
 *   Copyright (c) 2021 Akryllax (akryllax@gmail.com)

 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <cinttypes>
#include <sys/socket.h>
#include <memory>

namespace Networking
{
    typedef enum
    {
        CLIENT,
        SERVER
    } socket_mode_t;

    class basic_socket
    {
    protected:
        int port = 80; // The port you want to uses
        size_t address_len;
        int sockfd;
        socket_mode_t socket_mode;

    public:
        basic_socket(int domain, int type, int protocol);
        ~basic_socket();

        bool isServer() { return this->socket_mode == socket_mode_t::CLIENT; };

        int get_fd() { return this->sockfd; };

        virtual int bind(const struct sockaddr *addr, socklen_t addlen);
        virtual int listen(int sockfd, int backlog);
        virtual int accept();
        virtual int connect(const struct sockaddr *add, socklen_t addrlen);

        template<typename T>
        static std::shared_ptr<T> getServerSocket();
    };

    class TCPSocket : public basic_socket
    {
    public:
        TCPSocket(int domain, int type, int protocol);
    };

    class UDPSocket : public basic_socket
    {
    public:
        UDPSocket(int domain, int type, int protocol);
    };
} // namespace Networking
