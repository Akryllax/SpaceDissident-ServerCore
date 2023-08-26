#include "INetworkChannel.h"
#include "NetworkChannel.h"
#include "UDPServer.h"
#include "basic_setup.h"
#include "networklib.h"
#include "gtest/gtest.h"
#include <memory>
#include <random>

constexpr uint16_t BASE_PORT = 25000;

uint16_t getRandomPort(const uint16_t& base_port = BASE_PORT, uint16_t maxRange = 256)
{
  return base_port + (rand() % maxRange);
}

TEST(NetworkLibTest, FakeTest)
{
  auto itf = std::make_unique<NetworkShared::NetworkInterface>();
  GTEST_ASSERT_EQ(5, itf->testFunction());
};

TEST(NetworkLibTest, UseNetworkChannel)
{
  std::unique_ptr<INetworkChannel> udpChannel = std::make_unique<UDPServer>("localhost", "12345");
  NetworkChannel netChannel(std::move(udpChannel));

  if(netChannel.isOpen())
  {
    netChannel.write("some data");
  }
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
