#pragma once
#include <stdexcept>

namespace url::errors
{
class UrlParsingError : public std::invalid_argument
{
public:
	static UrlParsingError InvalidUrl();

	static UrlParsingError InvalidProtocol(const std::string& message);

	static UrlParsingError InvalidPort(const std::string& message);

	static UrlParsingError PortOutOfRange();

private:
	explicit UrlParsingError(const std::string& message);
};
}
