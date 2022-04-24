#pragma once
#include "map"
#include "string"
#include <optional>

class CTVSet
{
public:
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();
	int GetCurrentChannel() const;
	int GetPrevousChannel() const;
	bool SetChannel(int channel);
	bool SetChannel(std::string channel);
	bool SelectPrevousChannel();
	bool SetChannelName(int channel, std::string name);
	bool DeleteChannelName(std::string name);
	std::optional<std::string> GetChannelName(int channel);
	std::optional<int> GetChannelByName(std::string name);

private:
	bool m_isOn = false;
	int m_channel = 1;
	int m_prevChannel = m_channel;
	std::map<std::string, int> m_channelAliasList;
	
	std::map<std::string, int>::iterator GetExistChannelName(int channel);
	static bool IsValidChannelNumber(int channel);
};