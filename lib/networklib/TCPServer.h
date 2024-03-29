#pragma once

#include "INetworkChannel.h"
#include "NetworkUtils.h"
#include "TCPSession.h"
#include <boost/asio.hpp>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

using boost::asio::ip::tcp;
using SessionIDClientPair = std::pair<uint16_t, std::shared_ptr<TcpSession>>;
class TCPServer
{
public:
  // Constants and Static Members
  static constexpr int BUFFER_SIZE = 1024;
  static inline uint16_t LAST_SESSION_ID = 0;

  // Constructors and Destructors
  TCPServer(boost::asio::io_context& io_context, const std::string& port);
  ~TCPServer();

  // Public Methods
  bool isOpen() const;
  void processIncomingMessages();
  void writeAllPending();
  void close();
  void readAllIncoming();
  auto getClient(uint16_t sessionID);

  //Data managment API
  bool anyClientHasIncoming() const;
  std::vector<SessionIDClientPair> getClientsWithPendingData() const;
  std::optional<std::pair<uint16_t, std::vector<std::string>>> getIncomingForSession(uint16_t id);

private:
  // Private Members
  boost::asio::io_context& io_context_;
  tcp::acceptor acceptor_;
  tcp::socket socket_;
  std::map<uint16_t, std::shared_ptr<TcpSession>> clientSessions_;
  std::vector<uint16_t> sessionsWithPendingIncoming;
  std::vector<uint16_t> sessionsWithPendingOutcoming;

  // Private Methods
  void do_accept();
};