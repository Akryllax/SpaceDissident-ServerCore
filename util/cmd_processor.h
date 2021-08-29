#pragma once

#include <memory>
#include <string>
#include <vector>

typedef enum
{
    // Command result
    CMD_RESULT_OK,
    CMD_RESULT_ERROR,
    CMD_RESULT_INVALID_ARGUMENT,
    CMD_RESULT_INVALID_COMMAND,
    CMD_RESULT_INVALID_COMMAND_ARGUMENT,
    CMD_RESULT_INVALID_COMMAND_ARGUMENT_COUNT
} cmd_result_t;

class Command
{
public:
    Command();
    ~Command();

    const std::string getName() const;
    const std::string getDescription() const;
    const std::string getUsage() const;
    const std::string getHelp() const;

    virtual bool run(const std::vector<std::string> &args);

protected:
    std::string name;
    std::string description;
    std::string usage;
    std::string help;

    uint8_t argCount;
};

class CommandQueue
{
protected:
    std::vector<std::unique_ptr<Command>> commands;

public:
    CommandQueue();
    ~CommandQueue();

    void addCommand(std::shared_ptr<Command> command);
    void processCommands();
};

class CommandProcessor
{
public:
    CommandProcessor();
    ~CommandProcessor();

    void addCommand(Command *command);
    // cmd_result_t processCommand(const char *command);
};

void CommandProcessor::addCommand(Command *command){

};

