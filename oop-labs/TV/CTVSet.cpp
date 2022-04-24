#include "CTVSet.h"
#include "..\ToolsLib\StringsFunctions.h"
#include "..\ToolsLib\MapFunctions.h"

bool CTVSet::IsTurnedOn() const
{
	return m_isOn;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

int CTVSet::GetCurrentChannel() const
{
	return IsTurnedOn() ? m_channel : 0;
}

int CTVSet::GetPrevousChannel() const
{
	return IsTurnedOn() ? m_prevChannel : 0;
}

bool CTVSet::SetChannel(int channel)
{
	if (!IsTurnedOn() || !IsValidChannelNumber(channel))
	{
		return false;
	}
	m_prevChannel = m_channel;
	m_channel = channel;
	return true;
}

bool CTVSet::SetChannel(std::string channel)
{
	if (!IsTurnedOn() || m_channelAliasList.count(channel) == 0)
	{
		return false;
	}
	m_prevChannel = m_channel;
	m_channel = m_channelAliasList[channel];
	return true;
}

bool CTVSet::SelectPrevousChannel()
{
	return SetChannel(GetPrevousChannel());
}

bool CTVSet::SetChannelName(int channel, std::string name)
{
	if (!IsTurnedOn() || !IsValidChannelNumber(channel))
	{
		return false;
	}
	std::string n = StringsFunctions::RemoveExtraSpaces(name);
	if (n.empty())
	{
		return false;
	}
	auto result = GetExistChannelName(channel);
	if (result != m_channelAliasList.end())
	{
		m_channelAliasList.erase(result);
	}
	m_channelAliasList[n] = channel;
	return true;
}

bool CTVSet::DeleteChannelName(std::string name)
{
	if (m_channelAliasList.count(name) == 0)
	{
		return false;
	}
	m_channelAliasList.erase(name);
	return true;
}

std::optional<std::string> CTVSet::GetChannelName(int channel)
{
	auto result = GetExistChannelName(channel);
	if (result == m_channelAliasList.end())
	{
		return std::nullopt;
	}
	return result->first;
}

std::optional<int> CTVSet::GetChannelByName(std::string name)
{
	if (m_channelAliasList.count(name) == 0)
	{
		return std::nullopt;
	}
	return m_channelAliasList[name];
}

std::map<std::string, int>::iterator CTVSet::GetExistChannelName(int channel)
{
	auto result = MapFunctions::FindAll(m_channelAliasList.begin(), m_channelAliasList.end(), [channel](std::pair<std::string, int> item) -> bool {
		return item.second == channel;
	});
	if (result.empty())
	{
		return m_channelAliasList.end();
	}
	return result[0];
}

bool CTVSet::IsValidChannelNumber(int channel)
{
	return (channel >= 1 && channel <= 99);
}
