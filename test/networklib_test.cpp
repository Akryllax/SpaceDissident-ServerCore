#include "INetworkChannel.h"
#include "NetworkChannel.h"
#include "TCPServer.h"
#include "TCPSession.h"
#include "UDPClient.h"
#include "UDPServer.h"
#include "basic_setup.h"
#include "networklib.h"
#include "gtest/gtest.h"
#include <chrono>
#include <cstdint>
#include <memory>
#include <random>
#include <thread>

constexpr uint16_t BasePort = 25000;

class TCPSessionTest : public ::testing::Test
{
public:
  void TestMultipleMessage()
  {
    boost::asio::io_context io_context;
    tcp::socket socket(io_context);
    TcpSession session(std::move(socket), 1);

    session.incoming_messages_.push("Hello");
    session.incoming_messages_.push("World");

    ASSERT_TRUE(session.hasIncomingMessages());

    auto message1 = session.popIncomingMessage();
    ASSERT_TRUE(message1.has_value());
    ASSERT_EQ(message1.value(), "Hello");

    auto message2 = session.popIncomingMessage();
    ASSERT_TRUE(message2.has_value());
    ASSERT_EQ(message2.value(), "World");

    ASSERT_FALSE(session.hasIncomingMessages());
  }

  void TestQueueManagement()
  {
    boost::asio::io_context io_context;
    tcp::socket socket(io_context);
    TcpSession session(std::move(socket), 1);

    // Simulate incoming message
    session.incoming_messages_.push("Hello");

    // Check if the message is queued
    ASSERT_TRUE(session.hasIncomingMessages());

    // Pop the message and check
    auto message = session.popIncomingMessage();
    ASSERT_TRUE(message.has_value());
    ASSERT_EQ(message.value(), "Hello");

    // Check if the queue is empty now
    ASSERT_FALSE(session.hasIncomingMessages());
  }
};

uint16_t GenerateRandomPort(uint16_t basePort = BasePort, uint16_t maxRange = 256)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(basePort, basePort + maxRange);
  return distr(gen);
}

TEST(NetworkLibTest, Test_LibAccessible)
{
  auto networkInterface = std::make_unique<NetworkShared::NetworkInterface>();
  ASSERT_EQ(networkInterface->testFunction(), 5);
}

TEST(NetworkLibTest, UseNetworkChannel)
{
  const uint16_t randomPort = GenerateRandomPort();
  const std::string portStr = std::to_string(randomPort);

  auto udpServer = std::make_unique<UDPServer>("127.0.0.1", portStr);
  NetworkChannel serverChannel(std::move(udpServer));

  auto udpClient = std::make_unique<UDPClient>("127.0.0.1", portStr);
  NetworkChannel clientChannel(std::move(udpClient));

  std::thread serverThread([&]() {
    serverChannel.run(); // Ensure NetworkChannel has a run() method
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  ASSERT_TRUE(serverChannel.isOpen());
  ASSERT_TRUE(clientChannel.isOpen());

  ASSERT_TRUE(clientChannel.write("some data"));

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  std::vector<std::string> receivedData = serverChannel.read();
  ASSERT_FALSE(receivedData.empty());
  EXPECT_EQ(receivedData[0], "some data");

  serverChannel.close();
  clientChannel.close();

  if(serverThread.joinable())
  {
    serverThread.join();
  }
}

TEST_F(TCPSessionTest, QueueManagement)
{
  TestQueueManagement();
}

TEST_F(TCPSessionTest, EmptyQueue)
{
  boost::asio::io_context io_context;
  tcp::socket socket(io_context);
  TcpSession session(std::move(socket), 1);

  ASSERT_FALSE(session.hasIncomingMessages());
  auto message = session.popIncomingMessage();
  ASSERT_FALSE(message.has_value());
}

TEST_F(TCPSessionTest, MultipleMessages)
{
  TestMultipleMessage();
}

int main(int argc, char** argv)
{
  spdlog_init("network_lib_gtest.log");
  auto logger = spdlog::get("multi_sink");
  logger->set_level(spdlog::level::trace);
  spdlog::flush_on(spdlog::level::trace);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
