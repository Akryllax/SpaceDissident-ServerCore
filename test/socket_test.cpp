#include "gtest/gtest.h"
#include "basic_setup.h"
#include "akrsocket.h"


TEST(akrsocket_test, akrsocker_serv_basic)
{

};

const char* generateTCPPacket(const char* data, int len)
{
    char* packet = new char[len + 4];
    packet[0] = 0x00;
    packet[1] = 0x00;
    packet[2] = 0x00;
    packet[3] = len;
    memcpy(packet + 4, data, len);
    return packet;
}

int main(int argc, char **argv)
{
    spdlog_init("gameobject_gtest.log");
    auto logger = spdlog::get("multi_sink");
    logger->set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
