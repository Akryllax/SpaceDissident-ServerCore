// #include "asio/"
#include <ctime>
#include <iostream>
#include <string>
// #include <boost/array.hpp>
// #include <boost/bind/bind.hpp>
// #include <boost/shared_ptr.hpp>
#include <asio.hpp>

int main()
{
    try
    {
        asio::io_context io_context;
        udp_server server(io_context);
        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
