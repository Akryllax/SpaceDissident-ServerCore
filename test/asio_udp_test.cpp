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
  void SetUp(){};
  void TearDown(){};
};

TEST_F(UDPTest, UDPConnectionTest)
{
  // Create the IO context and client and server objects
  boost::asio::io_context io_context;
  UDPServer server(io_context, "127.0.0.1", "8081");
  UDPClient client(io_context, "127.0.0.1", "8081");

  // Create threads for the server and client
  std::thread server_thread([&]() { server.run(); });
  std::thread client_thread([&]() {
    client.start();
    client.write("Test message");
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

int main(int argc, char** argv)
{
  // Enable logging of std::cerr output
  testing::GTEST_FLAG(also_run_disabled_tests) = true;

  // Run the testswda
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
