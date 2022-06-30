#include "pch.h"
#include "HTTPUrl.h"
#include "UrlParsingError.h"

#include <optional>
#include <regex>

namespace
{
std::optional<std::smatch> Parse(const std::regex& regex, const std::string& input)
{
	std::smatch result;
	if (std::regex_match(input, result, regex))
	{
		return result;
	}
	return std::nullopt;
}
}

namespace url
{
using namespace protocols;
using namespace errors;

const std::regex url_regex(R"((.*)://([0-9A-Za-z\-.]+)(?::(\d+))?(?:/(.*))?)", std::regex::icase);

HTTPUrl::HTTPUrl(std::string const& url)
{
	const auto parsedUrl = Parse(url_regex, url);
	if (parsedUrl == std::nullopt)
	{
		throw UrlParsingError::InvalidUrl();
	}
	m_protocol = ParseProtocol(parsedUrl.value()[1]);
	m_domain = ParseDomain(parsedUrl.value()[2]);
	m_port = !parsedUrl.value()[3].str().empty() ? ParsePort(parsedUrl.value()[3]) : GetDefaultPortMap().at(m_protocol);
	m_document = ParseDocument(parsedUrl.value()[4]);
}

HTTPUrl::HTTPUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_domain(domain)
	  , m_document(document)
	  , m_protocol(protocol)
	  , m_port(GetDefaultPortMap().at(protocol))
{
	checkDomain(domain);
	checkDocument(document);
}

HTTPUrl::HTTPUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_domain(domain)
	  , m_document(document)
	  , m_protocol(protocol)
	  , m_port(port)
{
	checkDomain(domain);
	checkDocument(document);
	checkPort(port);
}

std::string HTTPUrl::GetURL() const
{
	const auto protocol = GetProtocol();
	std::string url = ProtocolToString(protocol);
	url.append("://");
	url.append(GetDomain());
	if (IsDefaultPort())
	{
		url.append(PortToString(m_port));
	}
	url.append(GetDocument());
	return url;
}

std::string HTTPUrl::GetDomain() const
{
	return m_domain;
}

std::string HTTPUrl::GetDocument() const
{
	return m_document;
}

Protocol HTTPUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short HTTPUrl::GetPort() const
{
	return m_port;
}

bool HTTPUrl::IsDefaultPort() const
{
	return GetDefaultPortMap().at(m_protocol) != m_port;
}

std::string HTTPUrl::ParseDomain(std::string const& domain) const
{
	checkDomain(domain);
	return domain;
}

std::string HTTPUrl::ParseDocument(std::string const& document) const
{
	std::string result("/");
	if (document.empty())
	{
		return result;
	}
	if (document[0] == '/')
	{
		result.append(document.substr(1));
	}
	else
	{
		result.append(document);
	}
	return result;
}

Protocol HTTPUrl::ParseProtocol(std::string const& protocol) const
{
	try
	{
		return ProtocolFromString(protocol);
	}
	catch (const std::exception& ex)
	{
		throw UrlParsingError::InvalidProtocol(ex.what());
	}
}

unsigned short HTTPUrl::ParsePort(std::string const& port) const
{
	int result;
	try
	{
		result = std::stoi(port);
	}
	catch (const std::exception& ex)
	{
		throw UrlParsingError::InvalidPort(ex.what());
	}
	checkPort(result);
	return static_cast<unsigned short>(result);
}

void HTTPUrl::checkPort(unsigned long port) const
{
	if (port <= 0 || port > std::numeric_limits<unsigned short>::max())
	{
		throw UrlParsingError::PortOutOfRange();
	}
}

void HTTPUrl::checkDomain(const std::string& domain) const
{
	if (domain.empty())
	{
		throw UrlParsingError::InvalidUrl();
	}
}

void HTTPUrl::checkDocument(const std::string& document) const
{
	if (document.empty())
	{
		throw UrlParsingError::InvalidUrl();
	}
}

std::string HTTPUrl::PortToString(unsigned short port)
{
	std::string result(":");
	return result.append(std::to_string(port));
}
} // namespace url
