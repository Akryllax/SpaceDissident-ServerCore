#include <exception>
#include <gtest/gtest.h>
#include "TCPClient.h"
#include "TCPServer.h"
#include "UDPClient.h"
#include "UDPServer.h"
#include <chrono>
#include <iostream>
#include <ostream>
#include <thread>

class UDPTest : public testing::Test
{
protected:  // Note: Made them protected so derived classes can access
  void SetUp() override { /* Optional setup code */ }
  void TearDown() override { /* Optional teardown code */ }
};

TEST_F(UDPTest, UDPConnectionTest_Client2Server)
{
  // Create the IO context and client and server objects
  boost::asio::io_context io_context;
  UDPServer server(io_context, "127.0.0.1", "8081");
  UDPClient client(io_context, "127.0.0.1", "8081");

  // Create threads for the server and client
  std::thread server_thread([&]() { server.run(); });
  std::thread client_thread([&]() {
    client.write("Test message");  // Removed start() as it's unnecessary
    io_context.poll();
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  server.stop();

  // Wait for the threads to finish
  server_thread.join();
  client_thread.join();

  ASSERT_EQ(server.received_messages().size(), 1);
  ASSERT_EQ(server.received_messages()[0], "Test message");
}

TEST_F(UDPTest, DISABLED_UDPConnectionTest_Server2Client)
{
  // Create the IO context and client and server objects
  boost::asio::io_context io_context;
  UDPServer server(io_context, "127.0.0.1", "8081");
  UDPClient client(io_context, "127.0.0.1", "8081");

  // Create threads for the server and client
  // std::thread server_thread([&]() { server.run(); server.write(); });
  std::thread client_thread([&]() {
    client.receive();  // Removed start() as it's unnecessary
    io_context.poll();
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  server.stop();

  // Wait for the threads to finish
  // server_thread.join();
  client_thread.join();

  ASSERT_EQ(server.received_messages().size(), 1);
  ASSERT_EQ(server.received_messages()[0], "Test message");
}

int main(int argc, char** argv)
{
  // Enable logging of std::cerr output
  testing::GTEST_FLAG(also_run_disabled_tests) = true;

  // Run the tests
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
