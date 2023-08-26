#include "INetworkChannel.h"
#include "NetworkChannel.h"
#include "UDPServer.h"
#include "UDPClient.h"
#include "basic_setup.h"
#include "networklib.h"
#include "gtest/gtest.h"
#include <cstdint>
#include <memory>
#include <thread>
#include <random>
#include <chrono>

constexpr uint16_t BasePort = 25000;

uint16_t GenerateRandomPort(uint16_t basePort = BasePort, uint16_t maxRange = 256) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(basePort, basePort + maxRange);
    return distr(gen);
}

TEST(NetworkLibTest, FakeTest) {
    auto networkInterface = std::make_unique<NetworkShared::NetworkInterface>();
    ASSERT_EQ(networkInterface->testFunction(), 5);
}

TEST(NetworkLibTest, UseNetworkChannel) {
    const uint16_t randomPort = GenerateRandomPort();
    const std::string portStr = std::to_string(randomPort);

    auto udpServer = std::make_unique<UDPServer>("127.0.0.1", portStr);
    NetworkChannel serverChannel(std::move(udpServer));

    auto udpClient = std::make_unique<UDPClient>("127.0.0.1", portStr);
    NetworkChannel clientChannel(std::move(udpClient));

    std::thread serverThread([&]() {
        serverChannel.run();  // Ensure NetworkChannel has a run() method
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

    if (serverThread.joinable()) {
        serverThread.join();
    }
}

int main(int argc, char** argv) {
    spdlog_init("network_lib_gtest.log");
    auto logger = spdlog::get("multi_sink");
    logger->set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
