#include "TCPServer.h"

// Implementation of public methods
TCPServer::TCPServer(boost::asio::io_context& io_context, const std::string& port)
    : io_context_(io_context)
    , acceptor_(io_context_, tcp::endpoint(tcp::v4(), NetworkCore::Utils::convertToPort(port)))
    , socket_(io_context_)
{
  do_accept();
}

TCPServer::~TCPServer()
{
  for(const auto& clientSession : clientSessions_)
  {
    clientSession.second->close();
  }
}

bool TCPServer::isOpen() const
{
  return acceptor_.is_open();
}

void TCPServer::processIncomingMessages()
{
  for(const auto& [session_id, clientSession] : clientSessions_)
  {
    clientSession->read_incoming();
  }
}

void TCPServer::writeAllPending()
{
  for(const auto& [session_id, clientSession] : clientSessions_)
  {
    clientSession->write_pending();
  }
}

void TCPServer::close()
{
  acceptor_.close();
}

void TCPServer::readAllIncoming()
{
  for(const auto& [session_id, clientSession] : clientSessions_)
  {
    clientSession->read_incoming();
  }
}

auto TCPServer::getClient(uint16_t sessionID)
{
  return clientSessions_[sessionID];
}

// Implementation of private methods
void TCPServer::do_accept()
{
  acceptor_.async_accept(socket_, [this](boost::system::error_code ec) {
    if(!ec)
    {
      LAST_SESSION_ID++;
      auto tcpSession = std::make_shared<TcpSession>(std::move(socket_), LAST_SESSION_ID);
      clientSessions_.insert({tcpSession->SESSION_ID, tcpSession});
    }
    do_accept();
  });
}
