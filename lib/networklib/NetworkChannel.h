#include "INetworkChannel.h"
#include <memory>

class NetworkChannel
{
public:
    NetworkChannel(std::unique_ptr<INetworkChannel> channel)
        : channel_(std::move(channel))
    {}

    bool isOpen() const { return channel_->isOpen(); }
    bool write(const std::string& data) { return channel_->write(data); }
    std::vector<std::string> read() { return channel_->read(); }
    void close() { channel_->close(); }
    void run() { channel_->run(); }

private:
    std::unique_ptr<INetworkChannel> channel_;
};