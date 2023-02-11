#include "config_holder.h"
#include "gtest/gtest_prod.h"
#include <regex>
#include <string>
#include <vector>

typedef enum
{
  DONE_OK = 1,
  DONE_ERROR,
  PARSING,
  IDLE
} ConfigParserState_t;

typedef enum
{
  EMPTY = 0,
  COMMENT,
  VALUE_PAIR,
  TAG,
  UNKOWN
} ConfigParserLineType_t;

typedef std::pair<std::string, std::string> ConfigPair_t;

class BasicConfigParser
{
  FRIEND_TEST(UtilTest, BasicConfigParser_typecheks_Ok);
  FRIEND_TEST(UtilTest, BasicConfigParser_getLineType_Ok);

private:
  BasicConfigParser(){};
  ~BasicConfigParser(){};

  static const std::regex regexComment;
  static const std::regex rgx_valuePair;
  static const std::regex regexTag;
  static const std::regex regexEmpty;

protected:
  const inline static bool isValuePair(const std::string& line)
  {
    return !isCommentLine(line) && !isEmptyLine(line) && std::regex_match(line, rgx_valuePair);
  }

  const inline static bool isEmptyLine(const std::string& line)
  {
    return std::regex_match(line, regexEmpty);
  }

  const inline static bool isCommentLine(const std::string& line)
  {
    return std::regex_match(line, regexComment);
  }

  const inline static bool isTagLine(const std::string& line)
  {
    return std::regex_match(line, regexTag);
  }

  const static ConfigPair_t getValuePair(const std::string& line);

  const static ConfigParserLineType_t getLineType(const std::string& line);

  const static std::string getTag(const std::string& line);

public:
  static const ConfigHolder parse(const std::string& configString);
};

const std::regex BasicConfigParser::regexComment = std::regex("^\\s*?#.*\n");
const std::regex BasicConfigParser::rgx_valuePair =
    std::regex("^\\s*?([\\w\\d_]+)\\s*?=\\s*?([\\w\\d_\\s\\.,\\-!#@]+)\\s*?;?$");
const std::regex BasicConfigParser::regexTag = std::regex("^\\s*?\\[([\\w\\d_]+)\\]\\s*?;?\\s*?$");
const std::regex BasicConfigParser::regexEmpty = std::regex("^\\s*?$");

const ConfigHolder BasicConfigParser::parse(const std::string& configString)
{
  ConfigHolder config;

  std::istringstream f(configString);
  std::string fileLine, cmdLine;
  std::string lastTag = "Default";

  while(getline(f, fileLine, '\n')) //TODO!: refact this
  {
    std::stringstream fileLineStream(fileLine);
    while(getline(fileLineStream, cmdLine, ';'))
    {
      switch(getLineType(cmdLine))
      {
      case VALUE_PAIR: {
        auto valuePair = getValuePair(cmdLine);
        config.add(valuePair.first, valuePair.second);
        break;
      }
      case TAG:
        lastTag = ((getTag(cmdLine) != "") ? getTag(cmdLine) : lastTag);
        break;
      case EMPTY:
      case COMMENT:
      default:
        break;
      }
    }
  }

  return config;
}

const ConfigParserLineType_t BasicConfigParser::getLineType(const std::string& line)
{
  if(isEmptyLine(line))
  {
    return EMPTY;
  }
  else if(isCommentLine(line))
  {
    return COMMENT;
  }
  else if(isValuePair(line))
  {
    return VALUE_PAIR;
  }
  else if(isTagLine(line))
  {
    return TAG;
  }
  else
  {
    return UNKOWN;
  }
};

const ConfigPair_t BasicConfigParser::getValuePair(const std::string& line)
{
  ConfigPair_t pair;
  std::smatch match;

  std::regex_search(line, match, rgx_valuePair);
  pair.first = match[1];
  pair.second = match[2];

  return pair;
};

const std::string BasicConfigParser::getTag(const std::string& line)
{
  std::smatch match;
  std::regex_search(line, match, regexTag);
  return match[1];
}