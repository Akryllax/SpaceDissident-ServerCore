#include "NetworkChannel.h" // Assuming you have a NetworkChannel class in your net library
#include "ServerCoreModule.h"
#include "TCPServer.h" // Assuming you have a TCPServer class in your net library
#include <memory>

class TCPServerModule : public ServerCoreModule
{
private:
  std::unique_ptr<TCPServer> tcpServer;

public:
  static const uint16_t CORE_MOD_ID = 1001; // Some unique ID for this module

  virtual void onInitialize(const ServerContext& coreCtx) override
  {
    spdlog::trace("TCPServerModule::onInitialize()");
    tcpServer = std::make_unique<TCPServer>(, "8080");
  }

  virtual void onConfig(const ServerContext& coreCtx) override
  {
    spdlog::trace("TCPServerModule::onConfig()");
    // Any additional configuration logic here
  }

  virtual void onTick(const ServerContext& coreCtx) override
  {
    spdlog::trace("TCPServerModule::onTick()");
    // This will be called 30 times a second
    // Here you can read from or write to the network channel
    // For example:
    std::vector<std::string> receivedData = networkChannel->read();
    if(!receivedData.empty())
    {
      // Process received data
    }
  }
};
