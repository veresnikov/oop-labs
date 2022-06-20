#include "pch.h"
#include "Time.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace 
{
std::vector<std::string> Explode(std::string const& input, std::string const& separator)
{
	std::vector<std::string> result;
	size_t position = 0;
	size_t separatorPosition = input.find(separator, position);
	if (separatorPosition == std::string::npos)
	{
		result.push_back(input);
		return result;
	}

	while (position < input.length())
	{
		separatorPosition = input.find(separator, position);
		if (separatorPosition == std::string::npos)
		{
			result.push_back(input.substr(position));
			break;
		}
		result.push_back(input.substr(position, separatorPosition - position));
		position = separatorPosition + separator.length();
	}
	return result;
}
}

constexpr unsigned SECONDS_PER_HOUR = 60 * 60;
constexpr unsigned SECONDS_PER_MINUTE = 60;
constexpr unsigned MAX_TIMESTAMP = 23 * SECONDS_PER_HOUR + 59 * SECONDS_PER_MINUTE + 60;

Time::Time(unsigned hours, unsigned minutes, unsigned seconds)
	: Time(hours * SECONDS_PER_HOUR + minutes * SECONDS_PER_MINUTE + seconds)
{
	if (hours > 23 || minutes > 59 || seconds > 59 || hours < 0 || minutes < 0 || seconds < 0)
	{
		throw std::logic_error("Invalid input arguments");
	}
}

Time::Time(unsigned timestamp)
	: m_timestamp(timestamp)
{
	if (timestamp > MAX_TIMESTAMP || timestamp < 0)
	{
		throw std::logic_error("Invalid timestamp value");
	}
}

unsigned Time::GetHours() const
{
	return m_timestamp / SECONDS_PER_HOUR;
}

unsigned Time::GetMinutes() const
{
	return (m_timestamp - GetHoursTimestamp()) / SECONDS_PER_MINUTE;
}

unsigned Time::GetSeconds() const
{
	return m_timestamp - GetHoursTimestamp() - GetMinutesTimestamp();
}

Time& Time::operator++()
{
	auto t = TimestampAdjustmentForAdd(*this, 1);
	this->m_timestamp = t.m_timestamp;
	return *this;
}

Time Time::operator++(int)
{
	const Time old = *this;
	operator++();
	return old;
}

Time& Time::operator--()
{
	auto t = TimestampAdjustmentForSub(*this, 1);
	this->m_timestamp = t.m_timestamp;
	return *this;
}

Time Time::operator--(int)
{
	const Time old = *this;
	operator--();
	return old;
}

Time operator+(Time left, Time right)
{
	return Time::TimestampAdjustmentForAdd(left, right.m_timestamp);
}

Time operator-(Time left, Time right)
{
	return Time::TimestampAdjustmentForSub(left, right.m_timestamp);
}

Time operator*(Time time, int mul)
{
	return Time::TimestampAdjustmentForMul(time, mul);
}

Time operator/(Time time, int div)
{
	auto h = time.GetHours() / div;
	auto m = time.GetMinutes() / div;
	m += std::round(((static_cast<double>(time.GetHours()) / div - h) * SECONDS_PER_HOUR) / SECONDS_PER_MINUTE);
	auto s = time.GetSeconds() / div;
	time.m_timestamp = h * SECONDS_PER_HOUR + m * SECONDS_PER_MINUTE + s;
	return time;
}

unsigned operator/(Time time, Time div)
{
	return time.m_timestamp / div.m_timestamp;
}

Time Time::operator+=(Time right)
{
	this->m_timestamp = operator+(*this, right).m_timestamp;
	return *this;
}

Time Time::operator-=(Time right)
{
	this->m_timestamp = operator-(*this, right).m_timestamp;
	return *this;
}

Time Time::operator*=(int mul)
{
	this->m_timestamp = operator*(*this, mul).m_timestamp;
	return *this;
}

Time Time::operator/=(int div)
{
	this->m_timestamp = operator/(*this, div).m_timestamp;
	return *this;
}

Time operator*(int i, Time time)
{
	return time * i;
}

std::ostream& operator<<(std::ostream& stream, const Time& time)
{
	stream << std::setw(2) << std::setfill('0') << time.GetHours();
	stream << ":";
	stream << std::setw(2) << std::setfill('0') << time.GetMinutes();
	stream << ":";
	stream << std::setw(2) << std::setfill('0') << time.GetSeconds();
	return stream;
}

std::istream& operator>>(std::istream& stream, Time& time)
{
	std::string str;
	stream >> str;
	auto args = Explode(str, ":");
	if (args.size() != 3)
	{
		throw std::logic_error("Incorrect time string");
	}
	auto h = std::stoi(args[0]);
	auto m = std::stoi(args[1]);
	auto s = std::stoi(args[2]);
	if (h > 23 || m > 59 || s > 59 || h < 0 || m < 0 || s < 0)
	{
		throw std::logic_error("Invalid input arguments");
	}
	time.m_timestamp = h * SECONDS_PER_HOUR + m * SECONDS_PER_MINUTE + s;
	return stream;
}

bool Time::operator==(const Time& right) const
{
	return m_timestamp == right.m_timestamp;
}

bool Time::operator<(const Time& right) const
{
	return m_timestamp < right.m_timestamp;
}

bool Time::operator>(const Time& right) const
{
	return m_timestamp > right.m_timestamp;
}

bool Time::operator<=(const Time& right) const
{
	return m_timestamp <= right.m_timestamp;
}

bool Time::operator>=(const Time& right) const
{
	return m_timestamp >= right.m_timestamp;
}

unsigned Time::GetHoursTimestamp() const
{
	return GetHours() * SECONDS_PER_HOUR;
}

unsigned Time::GetMinutesTimestamp() const
{
	return GetMinutes() * SECONDS_PER_MINUTE;
}

Time Time::TimestampAdjustmentForAdd(Time time, unsigned diffTimestamp)
{
	time.m_timestamp += diffTimestamp;
	if (time.m_timestamp >= MAX_TIMESTAMP)
	{
		auto excess = time.m_timestamp / MAX_TIMESTAMP;
		time.m_timestamp -= excess * MAX_TIMESTAMP;
	}
	return time;
}

Time Time::TimestampAdjustmentForSub(Time time, unsigned diffTimestamp)
{
	auto temp = time.m_timestamp;
	time.m_timestamp -= diffTimestamp;
	if (time.m_timestamp > MAX_TIMESTAMP)
	{
		time.m_timestamp = MAX_TIMESTAMP;
		time.m_timestamp -= diffTimestamp;
		time.m_timestamp += temp;
	}
	return time;
}

Time Time::TimestampAdjustmentForMul(Time time, int mul)
{
	auto newTimestamp = time.GetHours() * mul * SECONDS_PER_HOUR + time.GetMinutes() * mul * SECONDS_PER_MINUTE + time.GetSeconds() * mul;
	if (newTimestamp >= MAX_TIMESTAMP)
	{
		auto excess = newTimestamp / MAX_TIMESTAMP;
		newTimestamp -= excess * MAX_TIMESTAMP;
	}
	time.m_timestamp = newTimestamp;
	return time;
}
