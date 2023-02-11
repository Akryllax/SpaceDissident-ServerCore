#include "basic_setup.h"
#include "networklib.h"
#include "gtest/gtest.h"

constexpr uint16_t BASE_PORT = 25000;

const uint16_t getRandomPort(const uint16_t& base_port, uint16_t maxRange = 256)
{
  return rand() % maxRange;
}

TEST(NetworkLibTest, FakeTest)
{
  auto* itf = new NetworkShared::NetworkInterface();
  GTEST_ASSERT_EQ(5, itf->testFunction());
  delete itf;
};

int main(int argc, char** argv)
{
  spdlog_init("network_lib_gtest.log");
  auto logger = spdlog::get("multi_sink");
  logger->set_level(spdlog::level::trace);
  spdlog::flush_on(spdlog::level::trace);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
