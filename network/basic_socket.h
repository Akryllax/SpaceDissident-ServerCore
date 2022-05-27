

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

    class BasicSocket
    {
    protected:
        int port = 80; // The port you want to use
        size_t address_len;
        int sockfd;
        socket_mode_t socket_mode;

    public:
        BasicSocket(int domain, int type, int protocol);
        ~BasicSocket();

        bool isServer() { return this->socket_mode == socket_mode_t::CLIENT; };

        int get_fd() { return this->sockfd; };

        virtual int bind(const struct sockaddr *addr, socklen_t addlen);
        virtual int listen(int sockfd, int backlog);
        virtual int accept();
        virtual int connect(const struct sockaddr *add, socklen_t addrlen);

        template<typename T>
        static std::shared_ptr<T> getServerSocket();
    };

    class TCPSocket : public BasicSocket
    {
    public:
        TCPSocket(int domain, int type, int protocol);

        int bind(const struct sockaddr *addr, socklen_t addlen);
    };

    class UDPSocket : public BasicSocket
    {
    public:
        UDPSocket(int domain, int type, int protocol);

        int bind(const struct sockaddr *addr, socklen_t addlen);
    };
} // namespace Networking
