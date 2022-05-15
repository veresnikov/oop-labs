#include "../ToolsLib/StringsFunctions.h"
#include "CTVSet.h"
#include <iostream>
#include <string>

const std::string SEPARATOR = " ";

void TurnOn(CTVSet& tv)
{
	tv.TurnOn();
	std::cout << "OK" << std::endl;
}

void TurnOff(CTVSet& tv)
{
	tv.TurnOff();
	std::cout << "OK" << std::endl;
}

void SelectChannel(CTVSet& tv, int channel)
{
	if (tv.SetChannel(channel))
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}
}

void Info(CTVSet& tv)
{
	if (tv.IsTurnedOn())
	{
		std::cout << "TV is turned on" << std::endl;
	}
	else
	{
		std::cout << "TV is turned off" << std::endl;
	}
	std::cout << "Current channel: " << tv.GetCurrentChannel() << std::endl;
	std::cout << "Prevous channel: " << tv.GetPrevousChannel() << std::endl;
	auto aliasList = tv.GetChannelAliasList();
	if (aliasList.empty())
	{
		std::cout << "Alias list empty" << std::endl;
	}
	else
	{
		for (auto i = aliasList.begin(); i != aliasList.end(); i++)
		{
			std::cout << i->second << " - " << i->first << std::endl;
		}
	}
}

void SelectPrevousChannel(CTVSet& tv)
{
	if (tv.SelectPrevousChannel())
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}
}

void SetChannelName(CTVSet& tv, std::string name, int channel)
{
	if (tv.SetChannelName(channel, name))
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}
}

void DeleteChannelName(CTVSet& tv, std::string name)
{
	if (tv.DeleteChannelName(name))
	{
		std::cout << "OK" << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}
}

void GetChannelName(CTVSet& tv, int channel)
{
	auto result = tv.GetChannelName(channel);
	if (result != std::nullopt)
	{
		std::cout << result.value() << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}
}

void GetChannelByName(CTVSet& tv, std::string name)
{
	auto result = tv.GetChannelByName(name);
	if (result != std::nullopt)
	{
		std::cout << result.value() << std::endl;
	}
	else
	{
		std::cout << "Fail" << std::endl;
	}
}

void ParseCommand(CTVSet& tv, std::string input)
{
	auto args = StringsFunctions::Explode(input, SEPARATOR);
	if (args.empty())
	{
		std::cout << "invalid input" << std::endl;
		return;
	}
	auto command = args[0];
	if (command == "TurnOn")
	{
		TurnOn(tv);
	}
	else if (command == "TurnOff")
	{
		TurnOff(tv);
	}
	else if (command == "SelectChannel")
	{
		if (args.size() < 2)
		{
			std::cout << "invalid command argument" << std::endl;
			return;
		}
		SelectChannel(tv, std::stoi(args[1]));
	}
	else if (command == "Info")
	{
		Info(tv);
	}
	else if (command == "SelectPrevousChannel")
	{
		SelectPrevousChannel(tv);
	}
	else if (command == "SetChannelName")
	{
		if (args.size() < 3)
		{
			std::cout << "invalid  command argument" << std::endl;
			return;
		}
		SetChannelName(tv, args[1], std::stoi(args[2]));
	}
	else if (command == "DeleteChannelName")
	{
		DeleteChannelName(tv, args[1]);
	}
	else if (command == "GetChannelName")
	{
		GetChannelName(tv, std::stoi(args[1]));
	}
	else if (command == "GetChannelByName")
	{
		GetChannelByName(tv, args[1]);
	}
	else if (command == "Help")
	{
		std::cout << "Supported command:\n"
				  << "1) TurnOn \n"
				  << "2) TurnOff \n"
				  << "3) SelectChannel \n"
				  << "4) SelectPrevousChannel \n"
				  << "5) SetChannelName \n"
				  << "6) DeleteChannelName \n"
				  << "7) GetChannelName \n"
				  << "8) GetChannelByName \n"
				  << "9) Info \n"
				  << "10) Help \n";
	}
	else
	{
		std::cout << "unsupported command" << std::endl;
	}
}

int main()
{
	CTVSet tv;

	std::string input;
	while (true)
	{
		getline(std::cin, input);
		ParseCommand(tv, input);
	}
}
