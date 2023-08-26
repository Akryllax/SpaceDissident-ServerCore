#include "INetworkChannel.h"
#include "NetworkUtils.h"
#include "TCPSession.h"
#include <boost/asio.hpp>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using boost::asio::ip::tcp;

class TCPServer : public INetworkChannel
{
public:
  static constexpr int BUFFER_SIZE = 1024;
  static inline uint16_t LAST_SESSION_ID = 0;

private:
  boost::asio::io_context& io_context_;
  tcp::acceptor acceptor_;
  tcp::socket socket_;

private:
  std::map<uint16_t, std::shared_ptr<TcpSession>> clientSessions_;

public:
  TCPServer(boost::asio::io_context& io_context, const std::string& port)
      : io_context_(io_context)
      , acceptor_(io_context_, tcp::endpoint(tcp::v4(), NetworkCore::Utils::convertToPort(port)))
      , socket_(io_context_)
  {
    do_accept();
  }

  ~TCPServer() override
  {
    for(const auto& clientSession : clientSessions_)
    {
      clientSession.second->close();
    }
  }

  void do_accept()
  {
    acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
      if(!ec)
      {
        LAST_SESSION_ID++;
        auto tcpSession = std::make_shared<TcpSession>(std::move(socket_), LAST_SESSION_ID);
        clientSessions_.insert({tcpSession->SESSION_ID,
                                tcpSession}); // Assuming get_session_id() is a method in TcpSession
        // TcpSession::start or similar handling logic
      }

      do_accept();
    });
  }

  bool isOpen() const override
  {
    return acceptor_.is_open();
  }

  void processIncomingMessages()
  {
    for(const auto& [session_id, clientSession] : clientSessions_)
    {
      // Process clientSession->incoming_messages_
      clientSession->read_incoming();
    }
  }

  bool write(const std::string& data = "") override
  {
    boost::system::error_code ec;

    for(const auto& [session_id, clientSession] : clientSessions_)
    {
      clientSession->write_pending(); // Assuming write_pending is a method in TcpSession

      if(ec)
      {
        std::cerr << "Sync write error: " << ec.message() << std::endl;
        return false; // Indicate failure
      }
    }
    return true; // Indicate success
  }

  void close() override
  {
    acceptor_.close();
  }

  std::vector<std::string> read() override
  {
    std::vector<std::string> receivedMessages;
    // Implement your TCP read logic here, you will likely need to iterate through clientSessions_
    return receivedMessages;
  }
};
