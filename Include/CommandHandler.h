#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <ArgumentList.h>
#include <Interpreter.h>
#include "Command.h"

class CommandHandler
{
private:
    std::vector<Command*> commands;

public:
    CommandHandler() = default;
    ~CommandHandler();
    Command* getCommand(const char* invoke);
    void addCommand(Command* command);
    CommandStatus executeCommand(const char* strCmd);
};