#pragma once
#include <string>
#include <ArgumentList.h>

enum class CommandStatus
{
    SUCCESS, ERROR, NOT_FOUND, DEPRECATED, USELESS, NO_SYNTAX
};

class Command
{
public:
    Command(const char* invoke);
    virtual CommandStatus Run(ArgumentList& al) = 0;
    std::string getInvoke();

private:
    std::string invoke;
};