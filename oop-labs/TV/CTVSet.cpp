#include "CTVSet.h"
#include "../ToolsLib/MapFunctions.h"
#include "../ToolsLib/StringsFunctions.h"

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

int CTVSet::GetPreviousChannel() const
{
	return IsTurnedOn() ? m_prevChannel : 0;
}

bool CTVSet::SetChannel(const int channel)
{
	if (!IsTurnedOn() || !IsValidChannelNumber(channel))
	{
		return false;
	}
	m_prevChannel = m_channel;
	m_channel = channel;
	return true;
}

bool CTVSet::SetChannel(const std::string& channel)
{
	if (!IsTurnedOn() || m_channelAliasList.count(channel) == 0)
	{
		return false;
	}
	m_prevChannel = m_channel;
	m_channel = m_channelAliasList[channel];
	return true;
}

bool CTVSet::SelectPreviousChannel()
{
	return SetChannel(GetPreviousChannel());
}

bool CTVSet::SetChannelName(const int channel, const std::string& channelName)
{
	if (!IsTurnedOn() || !IsValidChannelNumber(channel))
	{
		return false;
	}
	const std::string name = StringsFunctions::RemoveExtraSpaces(channelName);
	if (name.empty())
	{
		return false;
	}
	const auto result = GetExistChannelName(channel);
	if (result != m_channelAliasList.end())
	{
		m_channelAliasList.erase(result);
	}
	m_channelAliasList[name] = channel;
	return true;
}

bool CTVSet::DeleteChannelName(const std::string& name)
{
	if (!IsTurnedOn() || m_channelAliasList.count(name) == 0)
	{
		return false;
	}
	m_channelAliasList.erase(name);
	return true;
}

std::optional<std::vector<std::pair<std::string, int>>> CTVSet::GetChannelAliasList() const
{
	if (!IsTurnedOn())
	{
		return std::nullopt;
	}
	auto result = MapFunctions::Sort(m_channelAliasList, [](const std::pair<std::string, int>& first, const std::pair<std::string, int>& second) -> bool {
		return first.second < second.second;
	});
	return result;
}

std::optional<std::string> CTVSet::GetChannelName(const int channel)
{
	if (!IsTurnedOn())
	{
		return std::nullopt;
	}
	const auto result = GetExistChannelName(channel);
	if (result == m_channelAliasList.end())
	{
		return std::nullopt;
	}
	return result->first;
}

std::optional<int> CTVSet::GetChannelByName(const std::string& name)
{
	if (!IsTurnedOn())
	{
		return std::nullopt;
	}
	if (m_channelAliasList.count(name) == 0)
	{
		return std::nullopt;
	}
	return m_channelAliasList[name];
}

std::map<std::string, int>::iterator CTVSet::GetExistChannelName(int channel)
{
	auto result = MapFunctions::FindAll(m_channelAliasList.begin(), m_channelAliasList.end(), [channel](const std::pair<std::string, int>& item) -> bool {
		return item.second == channel;
	});
	if (result.empty())
	{
		return m_channelAliasList.end();
	}
	return result[0];
}

bool CTVSet::IsValidChannelNumber(const int channel)
{
	return (channel >= 1 && channel <= 99);
}
