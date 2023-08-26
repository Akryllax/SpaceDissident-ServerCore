#include "basic_setup.h"
#include "modules/test_core_module.h"
#include "server_core.h"
#include "modules/test_core_module.h"
#include "gtest/gtest.h"
#include <memory>

TEST(NetworkLibTest, FakeTest)
{
  auto serverCoreInstance = std::make_unique<ServerCore>();

  serverCoreInstance->initialize();
  serverCoreInstance->tick();
};

TEST(BasicMessageTest, addDecoratorBasic)
{
  auto serverCoreInstance = std::make_unique<ServerCore>();

  serverCoreInstance->initialize();
  serverCoreInstance->tick();
};

TEST(BasicMessageTest, addCoreModule)
{
  auto serverCoreInstance = std::make_unique<ServerCore>();

  serverCoreInstance->initialize();
  serverCoreInstance->tick();

  auto testCoreModule = std::make_unique<TestCoreModule>();
  serverCoreInstance->addCoreModule(std::move(testCoreModule));  // Use std::move

  serverCoreInstance->tick();
}

int main(int argc, char** argv)
{
  spdlog_init("server_core_test.log");
  auto logger = spdlog::get("multi_sink");
  logger->set_level(spdlog::level::trace);
  spdlog::flush_on(spdlog::level::trace);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
