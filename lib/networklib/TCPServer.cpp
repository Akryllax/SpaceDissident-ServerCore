#include "TCPServer.h"
#include <cstdint>
#include <string>
#include <utility>

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

bool TCPServer::anyClientHasIncoming() const
{
  return !this->sessionsWithPendingIncoming.empty();
}

std::vector<SessionIDClientPair> TCPServer::getClientsWithPendingData() const
{
  std::vector<SessionIDClientPair> clientsWithPendingData;

  for(const auto& sessionID : sessionsWithPendingIncoming)
  {
    auto it = clientSessions_.find(sessionID);
    if(it != clientSessions_.end())
    {
      clientsWithPendingData.push_back(*it);
    }
  }

  return clientsWithPendingData;
}

std::optional<std::pair<uint16_t, std::vector<std::string>>> TCPServer::getIncomingForSession(uint16_t id)
{
  // Find the TcpSession object corresponding to this session ID
  auto it = clientSessions_.find(id);
  if(it == clientSessions_.end())
  {
    // Session not found
    return std::nullopt;
  }

  std::shared_ptr<TcpSession> session = it->second;
  std::vector<std::string> incomingMessages;

  // Retrieve all incoming messages for this session
  while(session->hasIncomingMessages())
  {
    auto message = session->popIncomingMessage();
    if(message.has_value())
    {
      incomingMessages.push_back(message.value());
    }
  }

  // Remove the session ID from sessionsWithPendingIncoming
  sessionsWithPendingIncoming.erase(
      std::remove(sessionsWithPendingIncoming.begin(), sessionsWithPendingIncoming.end(), id),
      sessionsWithPendingIncoming.end());

  return std::make_pair(id, incomingMessages);
}
