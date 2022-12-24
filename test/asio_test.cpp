// #include "asio/"
#include <ctime>
#include <iostream>
#include <string>
// #include <boost/array.hpp>
// #include <boost/bind/bind.hpp>
// #include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "networklib.h"
#include <UDPServer.h>
#include <UDPClient.h>

const std::string PORT = "8081";

int main()
{
    try
    {
        boost::asio::io_context io_context_server;
        UDPServer server(io_context_server, 8081);
        std::cout << "Listening on " << PORT << std::endl;
        io_context_server.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    boost::asio::io_context io_context_client;
    UDPClient client(io_context_client, "localhost", PORT);
    client.write("Hello, world!");
    io_context_client.run();

    return 0;
}
