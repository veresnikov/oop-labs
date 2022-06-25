#include <iostream>
#include "../URL/HTTPUrl.h"

int main()
{
	std::string stringURL;
	while (std::cin >> stringURL)
	{
		std::cout << stringURL << std::endl;
		try
		{
			url::HTTPUrl url(stringURL);
			std::cout << "protocol: " << url::protocols::ProtocolToString(url.GetProtocol()) << std::endl
					  << "domain: " << url.GetDomain() << std::endl
					  << "port: " << url.GetPort() << std::endl
					  << "document: " << url.GetDocument() << std::endl
					  << "url: " << url.GetURL() << std::endl;
		}
		catch (const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
		}
	}
}
