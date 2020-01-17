#include <ArgumentList.h>
#include <iostream>
#include <string>
#include <Interpreter.h>
#include "Command.h"
#include "CommandHandler.h"
#include <vector>

class PrintCommand : public Command
{
public:
	PrintCommand()
		: Command("print")
	{}

	CommandStatus Run(ArgumentList& al) override
	{
		size_t index = al.getArgument("c");
		if(index < al.size())
		{
			Argument& arg = al[index];
			std::vector<std::string> subargs = arg.getSubArguments();
			if(subargs.size() == 1)
			{
				std::cout << subargs[0] << std::endl;
			}
			else
			{
				std::cout << "'c' Argument count not equal 1" << std::endl;
				return CommandStatus::USELESS;
			}
			
		}
		else
		{
			std::cout << "'c' Argument not found." << std::endl;
			return CommandStatus::USELESS;
		}
		
		return CommandStatus::SUCCESS;
	}
};

class HelpCommand : public Command
{
public:
	HelpCommand()
		: Command("help")
	{}

	CommandStatus Run(ArgumentList& al) override
	{
		std::cout << "Help: Command Handler Test\n";
		std::cout << "print <-c> <subarg1(message)> - Prints the message to your screen\n";
		std::cout << "help - This message\n";
		std::cout << "exit - Quits this test application" << std::endl;
		return CommandStatus::SUCCESS;
	}
};

class ExitCommand : public Command
{
public:
	ExitCommand()
		: Command("exit")
	{}

	CommandStatus Run(ArgumentList& al) override
	{
		size_t index = al.getArgument("break");
		if(index < al.size())
		{
			Argument& arg = al[index];
			if(arg.getStatus() == Argument::ArgumentStatus::WRITTEN_OUT)
			{
				std::cout << "Breaking (this argument is only for testing and has no other use)" << std::endl;
				return CommandStatus::DEPRECATED;
			}
			else
			{
				exit(0);
			}
		}
		else
		{
			exit(0);	
		}
		return CommandStatus::SUCCESS;
	}
};

int main(int argc, char** argv)
{
	CommandHandler hCmd;
	hCmd.addCommand(new PrintCommand);
	hCmd.addCommand(new HelpCommand);
	hCmd.addCommand(new ExitCommand);

	while(true)
	{
		std::cout << "CMD >> ";
		std::string line;
		std::getline(std::cin, line);
		CommandStatus status = hCmd.executeCommand(line.c_str());

		switch(status)
		{
			case CommandStatus::USELESS:
				std::cout << "Command has useless structure." << std::endl;
				break;

			case CommandStatus::NO_SYNTAX:
				std::cout << "Written command has no syntax." << std::endl;
				break;

			case CommandStatus::NOT_FOUND:
				std::cout << "No command found with this name." << std::endl;
				break;

			case CommandStatus::ERROR:
				std::cout << "Command error" << std::endl;
				break;

			case CommandStatus::DEPRECATED:
				std::cout << "Command is outdated." << std::endl;
				break;
		}
	}
	
}