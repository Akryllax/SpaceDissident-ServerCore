#include "TCPSession.h"
#include <iostream>

void TcpSession::write_pending()
{
  if(outgoing_messages_.empty())
  {
    return; // No messages to send
  }

  auto self(shared_from_this());
  boost::asio::async_write(socket_,
                           boost::asio::buffer(outgoing_messages_.front()),
                           [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                             if(!ec)
                             {
                               outgoing_messages_.pop(); // Remove the sent message from the queue
                               write_pending(); // Try to send the next message
                             }
                             else
                             {
                               std::cerr << "Write error: " << ec.message() << std::endl;
                               socket_.close();
                             }
                           });
}

void TcpSession::read_incoming()
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(data_, max_length),
                          [this, self](boost::system::error_code ec, std::size_t length) {
                            if(!ec)
                            {
                              std::string message(data_, length);
                              incoming_messages_.push(
                                  message); // Add the received message to the queue
                              read_incoming(); // Continue reading the next message
                            }
                            else
                            {
                              std::cerr << "Read error: " << ec.message() << std::endl;
                              socket_.close();
                            }
                          });
}

bool TcpSession::hasIncomingMessages() const
{
  return !incoming_messages_.empty();
}

std::optional<std::string> TcpSession::popIncomingMessage()
{
  if(incoming_messages_.empty())
  {
    return std::nullopt;
  }

  std::string message = incoming_messages_.front();
  incoming_messages_.pop();
  return message;
}