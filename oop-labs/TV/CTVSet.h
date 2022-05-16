#pragma once
#include <map>
#include <string>
#include <optional>
#include <vector>

class CTVSet
{
public:
	bool IsTurnedOn() const;
	void TurnOn();
	void TurnOff();
	int GetCurrentChannel() const;
	int GetPreviousChannel() const;
	bool SetChannel(int channel);
	bool SetChannel(const std::string& channel);
	bool SelectPreviousChannel();
	bool SetChannelName(int channel, const std::string& name);
	bool DeleteChannelName(const std::string& name);
	std::optional<std::vector<std::pair<std::string, int>>> GetChannelAliasList() const;
	std::optional<std::string> GetChannelName(int channel);
	std::optional<int> GetChannelByName(const std::string& name);

private:
	bool m_isOn = false;
	int m_channel = 1;
	int m_prevChannel = m_channel;
	std::map<std::string, int> m_channelAliasList;
	
	std::map<std::string, int>::iterator GetExistChannelName(int channel);
	static bool IsValidChannelNumber(int channel);
};