#include "pch.h"
#include "UrlParsingError.h"

namespace url::errors
{
UrlParsingError UrlParsingError::InvalidUrl()
{
	return UrlParsingError("invalid url");
}

UrlParsingError UrlParsingError::InvalidProtocol(const std::string& message)
{
	return UrlParsingError("invalid protocol. " + message);
}

UrlParsingError UrlParsingError::InvalidPort(const std::string& message)
{
	return UrlParsingError("invalid port. " + message);
}

UrlParsingError UrlParsingError::PortOutOfRange()
{
	return UrlParsingError("port out of range");
}

UrlParsingError::UrlParsingError(const std::string& message)
	: std::invalid_argument(message)
{
}
}
