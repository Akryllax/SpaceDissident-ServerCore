

#include "base_decorator.h"
#include "base_message.h"
#include "basic_setup.h"
#include "debug_decorator.h"
#include "deco.h"
#include "gtest/gtest.h"

TEST(BasicMessageTest, addDecoratorBasic)
{
  auto message = std::unique_ptr<BaseMessage>(new BaseMessage());
  ASSERT_NE(nullptr, message);

  ASSERT_TRUE(message->addDecorator<BaseDecorator>());
  ASSERT_EQ(1, message->getDecoratorCount());
  ASSERT_FALSE(message->addDecorator<BaseDecorator>());
};

TEST(BasicMessageTest, getDecorator)
{
  auto message = std::unique_ptr<BaseMessage>(new BaseMessage());
  ASSERT_NE(nullptr, message);

  ASSERT_TRUE(message->addDecorator<BaseDecorator>());
  ASSERT_NE(nullptr, message->getDecorator<BaseDecorator>());
};

TEST(BasicMessageTest, addGetDebugDecorator)
{
  auto message = std::unique_ptr<BaseMessage>(new BaseMessage());
  ASSERT_NE(nullptr, message);

  ASSERT_TRUE(message->addDecorator<DebugDecorator>());
  auto deco = message->getDecorator<DebugDecorator>();
  ASSERT_NE(nullptr, deco);
  ASSERT_EQ("DebugDecorator", deco->to_string());
  delete deco;
};

TEST(DebugDecoTest, to_string)
{
  auto debugDeco = std::unique_ptr<DebugDecorator>(new DebugDecorator);

  ASSERT_EQ("DebugDecorator", debugDeco->to_string());
};

TEST(DecoTest, searchDecoBasic_1)
{
  auto* message = new BaseMessage();

  auto baseDeco = new BaseDecorator();
  auto debugDeco = new DebugDecorator();

  std::vector<BaseDecorator*> baseDecoList = {baseDeco, debugDeco};

  auto deco_basic = DecoratorUtils::search_deco<BaseDecorator>(baseDecoList);
  auto deco_debug = DecoratorUtils::search_deco<DebugDecorator>(baseDecoList);

  ASSERT_NE(nullptr, deco_basic);
  ASSERT_NE(nullptr, deco_debug);
  ASSERT_EQ(2, baseDecoList.size());
  ASSERT_NE(deco_basic, deco_debug);
};

int main(int argc, char** argv)
{
  spdlog_init("basic_test_gtest.log");
  auto logger = spdlog::get("multi_sink");
  logger->set_level(spdlog::level::trace);
  spdlog::flush_on(spdlog::level::trace);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
