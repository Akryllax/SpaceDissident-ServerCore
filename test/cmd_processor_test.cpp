#include "basic_setup.h"
#include "config_parser.h"
#include "gtest/gtest.h"

TEST(CmdProcessorTest, isCompiling)
{
  spdlog::trace("Started isCompiling test");
  ASSERT_EQ(1, 1);
};

int main(int argc, char** argv)
{
  spdlog_init("cmdProcessor_gtest.log");
  auto logger = spdlog::get("multi_sink");
  logger->set_level(spdlog::level::trace);
  spdlog::flush_on(spdlog::level::trace);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};