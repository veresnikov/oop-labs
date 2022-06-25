#define CATCH_CONFIG_MAIN
#include "../URL/HTTPUrl.h"
#include "../catch2/catch.hpp"

using namespace url;

TEST_CASE("Positive tests")
{
	SECTION("Construct in args with port view")
	{
		REQUIRE(HTTPUrl(
				"testdomain.test",
				"/directory/document.format",
				protocols::Protocol::HTTP,
				80)
			.GetURL()
			== "http://testdomain.test/directory/document.format");
		REQUIRE(HTTPUrl(
				"testdomain.test",
				"/directory/document.format",
				protocols::Protocol::HTTP,
				8080)
			.GetURL()
			== "http://testdomain.test:8080/directory/document.format");
		REQUIRE(HTTPUrl(
				"testdomain.test",
				"/directory/document.format",
				protocols::Protocol::HTTPS,
				443)
			.GetURL()
			== "https://testdomain.test/directory/document.format");
		REQUIRE(HTTPUrl(
				"testdomain.test",
				"/directory/document.format",
				protocols::Protocol::HTTPS,
				8080)
			.GetURL()
			== "https://testdomain.test:8080/directory/document.format");
	}

	SECTION("Construct in args without port view")
	{
		SECTION("Check default http port")
		{
			HTTPUrl url(
				"testdomain.test",
				"/directory/document.format",
				protocols::Protocol::HTTP);
			REQUIRE(url.GetURL() == "http://testdomain.test/directory/document.format");
			REQUIRE(url.GetPort() == 80);
		}
		SECTION("Check default https port")
		{
			HTTPUrl url(
				"testdomain.test",
				"/directory/document.format",
				protocols::Protocol::HTTPS);
			REQUIRE(url.GetURL() == "https://testdomain.test/directory/document.format");
			REQUIRE(url.GetPort() == 443);
		}
	}

	SECTION("Construct in string url view")
	{
		SECTION("Http url without port")
		{
			HTTPUrl url("http://testdomain.test/directory/document.format");
			REQUIRE(url.GetProtocol() == protocols::Protocol::HTTP);
			REQUIRE(url.GetDomain() == "testdomain.test");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetDocument() == "/directory/document.format");
		}
		SECTION("Http url with port")
		{
			HTTPUrl url("http://testdomain.test:8080/directory/document.format");
			REQUIRE(url.GetProtocol() == protocols::Protocol::HTTP);
			REQUIRE(url.GetDomain() == "testdomain.test");
			REQUIRE(url.GetPort() == 8080);
			REQUIRE(url.GetDocument() == "/directory/document.format");
		}
		SECTION("Https url without port")
		{
			HTTPUrl url("https://testdomain.test/directory/document.format");
			REQUIRE(url.GetProtocol() == protocols::Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "testdomain.test");
			REQUIRE(url.GetPort() == 443);
			REQUIRE(url.GetDocument() == "/directory/document.format");
		}
		SECTION("Https url with port")
		{
			HTTPUrl url("https://testdomain.test:8080/directory/document.format");
			REQUIRE(url.GetProtocol() == protocols::Protocol::HTTPS);
			REQUIRE(url.GetDomain() == "testdomain.test");
			REQUIRE(url.GetPort() == 8080);
			REQUIRE(url.GetDocument() == "/directory/document.format");
		}
		SECTION("url with empty document")
		{
			HTTPUrl url("http://testdomain.test");
			REQUIRE(url.GetProtocol() == protocols::Protocol::HTTP);
			REQUIRE(url.GetDomain() == "testdomain.test");
			REQUIRE(url.GetPort() == 80);
			REQUIRE(url.GetDocument() == "/");

			HTTPUrl url2("http://testdomain.test/");
			REQUIRE(url2.GetProtocol() == protocols::Protocol::HTTP);
			REQUIRE(url2.GetDomain() == "testdomain.test");
			REQUIRE(url2.GetPort() == 80);
			REQUIRE(url2.GetDocument() == "/");
		}
	}
}

TEST_CASE("Negative tests")
{
	SECTION("Counstruct exceptions")
	{
		REQUIRE_THROWS(HTTPUrl(""));
		REQUIRE_THROWS(HTTPUrl("ftp://test.test"));
		REQUIRE_THROWS(HTTPUrl("ftp://"));
		REQUIRE_THROWS(HTTPUrl("http://test.test:0"));
		REQUIRE_THROWS(HTTPUrl("http://test.test:65536"));
		REQUIRE_THROWS(HTTPUrl("http://test.test:9999999999"));
		REQUIRE_THROWS(HTTPUrl("", "/", protocols::Protocol::HTTP));
		REQUIRE_THROWS(HTTPUrl("test.test", "", protocols::Protocol::HTTP));
		REQUIRE_THROWS(HTTPUrl("test.test", "/", protocols::Protocol::HTTP, 0));
		REQUIRE_THROWS(HTTPUrl("test.test", "/", protocols::Protocol::HTTP, 65536));
	}
}