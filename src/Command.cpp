#include <Command.h>

Command::Command(const char* invoke)
    : invoke(invoke)
{}

std::string Command::getInvoke()
{
    return this->invoke;
}