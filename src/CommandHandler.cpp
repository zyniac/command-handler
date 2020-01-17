#include "CommandHandler.h"

CommandHandler::~CommandHandler()
{
    for(Command* cmd : this->commands)
    {
        delete cmd;
    }
}

Command* CommandHandler::getCommand(const char* invoke)
{
    auto itr = std::find_if(this->commands.begin(), this->commands.end(), [&](Command* command) {
        return command->getInvoke() == invoke;
    });

    if(itr < this->commands.end())
    {
        return *itr;
    }
    else
    {
        return nullptr;
    }
    
}

void CommandHandler::addCommand(Command* command)
{
    this->commands.emplace_back(command);
}

CommandStatus CommandHandler::executeCommand(const char* strCmd)
{
    ArgumentList al = Interpreter::compileCommand(strCmd);
    if(!al.isValid())
    {
        return CommandStatus::NO_SYNTAX;
    }
    else
    {
        Command* command = this->getCommand(al.getInvoke().c_str());
        if(command != nullptr)
        {
            return command->Run(al);
        }
        else
        {
            return CommandStatus::NOT_FOUND;
        }
        
    }
    
}