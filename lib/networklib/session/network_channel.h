#include <memory>
#include "basic_socket.h"

namespace Networking
{
    class NetworkChannel
    {
    protected:
        std::unique_ptr<BasicSocket> m_socket;

        NetworkChannel();
        ~NetworkChannel();

    public:
        static std::shared_ptr<NetworkChannel> newInstance();
    };
} // namespace Networking
