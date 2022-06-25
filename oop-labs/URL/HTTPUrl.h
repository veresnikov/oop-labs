#pragma once
#include "Protocol.h"
#include <string>

namespace url
{
class HTTPUrl
{
public:
	HTTPUrl(std::string const& url);

	HTTPUrl(
		std::string const& domain,
		std::string const& document,
		protocols::Protocol protocol = protocols::Protocol::HTTP);

	HTTPUrl(
		std::string const& domain,
		std::string const& document,
		protocols::Protocol protocol,
		unsigned short port);

	std::string GetURL() const;

	std::string GetDomain() const;

	std::string GetDocument() const;

	protocols::Protocol GetProtocol() const;

	unsigned short GetPort() const;

private:
	std::string m_domain;
	std::string m_document;
	protocols::Protocol m_protocol;
	unsigned short m_port;

	std::string ParseDomain(std::string const& domain) const;

	std::string ParseDocument(std::string const& document) const;

	protocols::Protocol ParseProtocol(std::string const& protocol) const;

	unsigned short ParsePort(std::string const& port) const;

	void checkPort(unsigned long port) const;

	void checkDomain(const std::string& domain) const;

	void checkDocument(const std::string& document) const;

	static std::string PortToString(unsigned short protocol);
};
}
