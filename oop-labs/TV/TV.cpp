#include "CTVSet.h"
#include <iostream>
#include <string>

const char SEPARATOR = ' ';

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
}

void ParseCommand(CTVSet& tv, std::string input)
{
	size_t separatorPosition = input.find(SEPARATOR);
	std::string command = input.substr(0, separatorPosition);
	std::string argument = (separatorPosition != std::string::npos) ? input.substr(separatorPosition + 1) : "";
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
		if (argument != "")
		{
			SelectChannel(tv, std::stoi(argument));
		}
	}
	else if (command == "Info")
	{
		Info(tv);
	}
	else if (command == "Help")
	{
		std::cout << "Supported command:\n"
				  << "1) TurnOn \n"
				  << "2) TurnOff \n"
				  << "3) SelectChannel \n"
				  << "4) Info \n"
				  << "5) Help \n";
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
