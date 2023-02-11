#include "basic_setup.h"
#include "config_parser.h"
#include "gtest/gtest.h"

TEST(UtilTest, isCompiling)
{
  spdlog::trace("Started isCompiling test");
  ASSERT_EQ(1, 1);
};

TEST(UtilTest, BasicConfigParser_stringCleanup_Ok)
{
  std::string testConfig(
      "Hello\nWorld\nConfig_value   =something\nother_Value =     something  awdawd");

  BasicConfigParser::parse(testConfig);
};

TEST(UtilTest, BasicConfigParser_typecheks_Ok)
{
  std::string valuePair1("Config_value   =something\n");
  std::string valuePair2("      someOtherValue=123something    \n");
  std::string commentLine("#      someOtherValue=123something    \n");
  std::string tagLine("[SomeCategory];\n");
  std::string emptyLine("\n");

  ASSERT_TRUE(BasicConfigParser::isValuePair(valuePair1));
  ASSERT_TRUE(BasicConfigParser::isValuePair(valuePair2));
  ASSERT_FALSE(BasicConfigParser::isValuePair(commentLine));
  ASSERT_FALSE(BasicConfigParser::isValuePair(tagLine));
  ASSERT_FALSE(BasicConfigParser::isValuePair(emptyLine));

  ASSERT_TRUE(BasicConfigParser::isCommentLine(commentLine));
  ASSERT_FALSE(BasicConfigParser::isCommentLine(valuePair1));

  ASSERT_TRUE(BasicConfigParser::isEmptyLine(emptyLine));
  ASSERT_FALSE(BasicConfigParser::isEmptyLine(valuePair1));

  ASSERT_TRUE(BasicConfigParser::isTagLine(tagLine));
  ASSERT_FALSE(BasicConfigParser::isTagLine(valuePair1));
};

TEST(UtilTest, BasicConfigParser_getLineType_Ok)
{
  std::string valuePair1("Config_value   =something\n");
  std::string valuePair2("      someOtherValue=123something    \n");
  std::string commentLine("#      someOtherValue=123something    \n");
  std::string tagLine("[SomeCategory];\n");
  std::string emptyLine("\n");

  ASSERT_EQ(ConfigParserLineType_t::VALUE_PAIR, BasicConfigParser::getLineType(valuePair1));
  ASSERT_EQ(ConfigParserLineType_t::VALUE_PAIR, BasicConfigParser::getLineType(valuePair2));
  ASSERT_EQ(ConfigParserLineType_t::COMMENT, BasicConfigParser::getLineType(commentLine));
  ASSERT_EQ(ConfigParserLineType_t::TAG, BasicConfigParser::getLineType(tagLine));
  ASSERT_EQ(ConfigParserLineType_t::EMPTY, BasicConfigParser::getLineType(emptyLine));
};

TEST(UtilTest, ConfigHolder_AddTest)
{
  ConfigHolder configHolder;

  configHolder.add("Config_value", "something");
  ASSERT_EQ(configHolder.get("Config_value"), "something");

  configHolder.add("Config_value", "something else");
  ASSERT_EQ(configHolder.get("Config_value"), "something else");

  ASSERT_EQ(configHolder.get("NON_EXISTING"), "");
  ASSERT_EQ(configHolder.size(), 1);

  configHolder.add("DifferentKey", "else value");
  ASSERT_EQ(configHolder.get("DifferentKey"), "else value");
  ASSERT_EQ(configHolder.size(), 2);
}

TEST(UtilTest, ConfigParser_ParseBasicConfig)
{
  const std::string basicConfig = "someValue = 32\notherValue =  Hello World";

  auto configHolder = BasicConfigParser::parse(basicConfig);

  ASSERT_EQ(configHolder.get("someValue"), "32");
  ASSERT_EQ(configHolder.get("otherValue"), "Hello World");

  const std::string mixedConfig = "[Basic]\nthisSetting =     21;helloSetting = Please help "
                                  "meww\n[OtherTag]\nrenderDistance=1.35;netTick=60\n";
  auto configHolder2 = BasicConfigParser::parse(mixedConfig);

  ASSERT_EQ(configHolder2.get("thisSetting"), "21");
  ASSERT_EQ(configHolder2.get("helloSetting"), "Please help meww");
  ASSERT_EQ(configHolder2.get("renderDistance"), "1.35");
  ASSERT_EQ(configHolder2.get("netTick"), "60");
  ASSERT_EQ(configHolder2.size(), 4);
}

int main(int argc, char** argv)
{
  spdlog_init("util_gtest.log");
  auto logger = spdlog::get("multi_sink");
  logger->set_level(spdlog::level::trace);
  spdlog::flush_on(spdlog::level::trace);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
};