#pragma once

#include <vector>
#include <string>

class INetworkChannel
{
public:
    virtual ~INetworkChannel() = default;

    virtual bool isOpen() const = 0;
    virtual bool write(const std::string& data) = 0;
    virtual std::vector<std::string> read() = 0;
    virtual void close() = 0;
};