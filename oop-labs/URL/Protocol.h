#pragma once
#include <algorithm>
#include <iterator>
#include <map>
#include <stdexcept>
#include <string>

namespace 
{
inline std::string ToLower(const std::string& input)
{
	std::string result;
	std::transform(
		input.begin(),
		input.end(),
		std::back_inserter(result),
		[](const char& ch) -> char { return static_cast<char>(tolower(ch)); }
	);
	return result;
}
}

namespace url::protocols
{
enum class Protocol
{
	HTTP,
	HTTPS
};

inline std::map<Protocol, unsigned short> GetDefaultPortMap()
{
	return {
		{ Protocol::HTTP, 80 },
		{ Protocol::HTTPS, 443 },
	};
}

inline std::string ProtocolToString(Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return "http";
	case Protocol::HTTPS:
		return "https";
	}
	throw std::invalid_argument("invalid protocol");
}

inline Protocol ProtocolFromString(const std::string& protocol)
{
	const auto lowerProtocol = ToLower(protocol);
	if (lowerProtocol == "http")
	{
		return Protocol::HTTP;
	}
	if (lowerProtocol == "https")
	{
		return Protocol::HTTPS;
	}
	throw std::invalid_argument("invalid string protocol");
}
}
