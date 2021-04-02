#include <memory>

namespace NetworkShared
{
    class NetworkChannel
    {
    protected:
        NetworkChannel();
        ~NetworkChannel();
    public:
        static std::shared_ptr<NetworkChannel> newInstance();
    };
} // namespace NetworkShared
