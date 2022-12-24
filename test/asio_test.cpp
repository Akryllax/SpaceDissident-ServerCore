#include <exception>
#include <gtest/gtest.h>

#include "UDPClient.h"
#include "UDPServer.h"
#include <iostream>
#include <ostream>
#include <thread>

int main(int argc, char** argv)
{
  // Enable logging of std::cerr output
  testing::GTEST_FLAG(also_run_disabled_tests) = true;

  // Run the tests
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// TEST(UDPTest, ConnectionTest)
// {
//   try
//   {
//     boost::asio::io_context io_context;

//     // Define and initialize the server object
//     UDPServer server(io_context, "192.168.1.132", "80801");

//     std::cerr << "#AKR1" << std::endl << std::flush;

//     std::thread server_thread = std::thread([&]() {
//       server.run();
//     });

//     std::cerr << "#AKR2" << std::endl << std::flush;

//     // Create a client and send a message to the server
//     UDPClient client(io_context, "localhost", "80801");
//     client.write("Hello, server!");

//     // Wait for the server to receive the message
//     std::this_thread::sleep_for(std::chrono::seconds(1));

//     std::cerr << "#AKR3" << std::endl << std::flush;

//     // Check that the server received the message
//     auto received_messages = server.received_messages();
//     ASSERT_EQ(received_messages.size(), 1);
//     ASSERT_EQ(received_messages[0], "Hello, server!");

//     std::cerr << "#AKR4" << std::endl << std::flush;

//     // Shut down the server and wait for the background thread to finish
//     server.stop();
//     server_thread.join();
//   }
//   catch(const std::exception& e)
//   {
//     std::cerr << "Exception caught: " << e.what() << '\n';
//   }
// }

TEST(UDPTest, ConnectionTest)
{
  // Create the IO context and client and server objects
  boost::asio::io_context io_context;
  UDPServer server(io_context, "192.168.1.132", "80801");
  UDPClient client(io_context, "192.168.1.132", "80801");

  // Create threads for the server and client
  std::thread server_thread([&]() { server.run(); });
  std::thread client_thread([&]() { client.write("Test message"); });

  // Wait for the threads to finish
  server_thread.join();
  client_thread.join();
}